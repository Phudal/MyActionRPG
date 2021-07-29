// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Components/CanvasPanelSlot.h"

#include "Widget/ClosableWnd/ClosableWnd.h"
#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/Button.h"
#include "DraggableWndTitle/DraggableWndTitle.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// â ũ�⸦ ������
	WndSize = FVector2D(500.0f, 600.0f);

	BP_DraggableWndTitle->SetTargetWidget(this);

	// �巡���� ���۵� �� �� â�� �ֻ������ ��ġ
	BP_DraggableWndTitle->OnDraggingStarted.AddLambda(
		[this]() {WidgetController->SetHighestPriorityWnd(this); });

	SetCloseButton(BP_DraggableWndTitle->GetCloseButton());
}

void UClosableWnd::SetCloseButton(UButton* closeButton)
{
	(CloseButton = closeButton)->OnClicked.AddDynamic(this, &UClosableWnd::CloseThisWnd);
}

UClosableWnd* UClosableWnd::CreateChildClosableWnd(TSubclassOf<UClosableWnd> closableWndClass, bool bUsePrevPosition,
	EInputModeType changeInputMode, bool bShowMouseCursor)
{
	// �ڽ� â�� ������
	auto childWnd = WidgetController->CreateWnd(
	closableWndClass, bUsePrevPosition,
		changeInputMode, bShowMouseCursor);

	// ������ �ڽ� â�� �θ� â�� �ڽ����� ����
	childWnd->ParentWnd = this;

	// �迭�� �߰���
	ChildWnds.Add(childWnd);

	// ������ �ڽ� â�� ��ȯ��
	return childWnd;
}

void UClosableWnd::CloseThisWnd()
{
	if (bBeClose)
		return;

	WidgetController->CloseWnd(false, this);
}

void UClosableWnd::CloseAllChildWnd()
{
	// �ڽ� â�� �����Ѵٸ�
	if (ChildWnds.Num() != 0)
	{
		// ��� �ڽ� â�� ������
		for (int32 i = 0; i < ChildWnds.Num(); i++)
		{
			auto childWnd = ChildWnds[i];

			if (IsValid(childWnd))
			{
				// �� ���� â�̶�� �������� ����
				if (childWnd->bBeClose)
					continue;;

				WidgetController->CloseWnd(false, childWnd);
			}
		}

		ChildWnds.Empty();
	}
}

void UClosableWnd::DetachFromParent()
{
	// �θ� â�� �����Ѵٸ�
	if (IsValid(ParentWnd))
	{
		ParentWnd->ChildWnds.Remove(this);
	}
}

UCanvasPanelSlot* UClosableWnd::GetCanvasPanelSlot() const
{
	return Cast<UCanvasPanelSlot>(Slot);
}

void UClosableWnd::SetTitleText(FText newTitleText)
{
	BP_DraggableWndTitle->SetTitleText(newTitleText);
}