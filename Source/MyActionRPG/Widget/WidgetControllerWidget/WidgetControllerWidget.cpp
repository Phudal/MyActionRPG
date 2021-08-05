// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Actor/Controller/BasePlayerController.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"

#include "Widget/ClosableWnd/MessageBoxWnd/MessageBoxWnd.h"
#include "Widget/ClosableWnd/ClosableWnd.h"


UWidgetControllerWidget::UWidgetControllerWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UMessageBoxWnd> BP_MESSAGE_BOX_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/MessageBoxWnd/BP_MessageBoxWnd.BP_MessageBoxWnd_C'"));

	if (BP_MESSAGE_BOX_WND.Succeeded())
		BP_MessageBoxWnd = BP_MESSAGE_BOX_WND.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> BP_MESSAGE_BOX_BACKGROUND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/MessageBoxWnd/BP_MessageBoxBackground.BP_MessageBoxBackground_C'"));

	if (BP_MESSAGE_BOX_BACKGROUND.Succeeded())
		BP_MessageBoxBackground = BP_MESSAGE_BOX_BACKGROUND.Class;
}

void UWidgetControllerWidget::InitializeWidgetControllerWidget(ABasePlayerController* basePlayerController)
{
	PlayerController = basePlayerController;
}

void UWidgetControllerWidget::ResetInputMode(bool bForceChange)
{
	// ���� â�� ������ �������� �ʴ´ٸ� �Է� ��带 ������
	if (bForceChange ||
		((AllocatedWnds.Num() == 0) && (AllocatedWidgets.Num() == 0)))
	{
		// �Է� ��带 ����
		PlayerController->ChangeInputModeToDefault();

		// Ŀ�� ǥ��
		PlayerController->bShowMouseCursor = PlayerController->GetDefaultCursorVisibility();
	}
}

void UWidgetControllerWidget::SaveWndPosition(const UClosableWnd* closableWnd)
{
	FString wndClsName = closableWnd->GetClass()->GetName();
	FVector2D wndPosition = closableWnd->GetCanvasPanelSlot()->GetPosition();

	if (PrevClosedWndPosition.Contains(wndClsName))
		PrevClosedWndPosition[wndClsName] = wndPosition;

	else
		PrevClosedWndPosition.Add(wndClsName, wndPosition);
}

UMessageBoxWnd* UWidgetControllerWidget::CreateMessageBox(FText titleText, FText msg, bool bUseBackground,
	uint8 buttons)
{
	UUserWidget* msgBoxBackground = nullptr;
	
	if (bUseBackground)
	{
		msgBoxBackground = CreateWidget<UUserWidget>(this, BP_MessageBoxBackground);
		CanvasPanel_WndParent->AddChildToCanvas(msgBoxBackground);

		UCanvasPanelSlot* messageBoxCanvasPanelSlot = Cast<UCanvasPanelSlot>(msgBoxBackground->Slot);
		messageBoxCanvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		messageBoxCanvasPanelSlot->SetOffsets(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
	}

	UMessageBoxWnd* msgBox = Cast<UMessageBoxWnd>(
		CreateWnd(BP_MessageBoxWnd, false, EInputModeType::IM_UIOnly, true));

	msgBox->MsgBoxBackground = msgBoxBackground;

	msgBox->InitializeMeesageBox(titleText, msg, buttons);

	return msgBox;
}

UClosableWnd* UWidgetControllerWidget::CreateWnd(TSubclassOf<UClosableWnd> wndClass, bool bUsePrevPosition,
	EInputModeType changeInputMode, bool bShowMouseCursor, float alignmentX, float alignmentY, float anchorMinX,
	float anchorMinY, float anchorMaxX, float anchorMaxY)
{
	// ���ο� â ������ ������
	UClosableWnd* newClosableWnd = CreateWidget<UClosableWnd>(this, wndClass);
	newClosableWnd->WidgetController = this;

	// �Ҵ�� â �迭�� �߰�
	AllocatedWnds.Add(newClosableWnd);

	// CanvasPanel_WndParent �� �ڽ� �������� �߰���
	CanvasPanel_WndParent->AddChild(newClosableWnd);

	// Anchor / Alignment ����
	auto wndCanvansPanelSlot = newClosableWnd->GetCanvasPanelSlot();
	wndCanvansPanelSlot->SetAnchors(FAnchors(anchorMinX, anchorMinY, anchorMaxX, anchorMaxY));
	wndCanvansPanelSlot->SetAlignment(FVector2D(alignmentX, alignmentY));

	// â ũ�⸦ ������
	wndCanvansPanelSlot->SetSize(newClosableWnd->GetWndSize());

	// ���� â ��ġ�� ����Ѵٸ�
	if (bUsePrevPosition)
	{
		// ���� â ��ġ�� ��ϵǾ� �ִ��� Ȯ����
		if (PrevClosedWndPosition.Contains(wndClass->GetName()))
		{
			// â ��ġ�� ���� ��ġ�� ������
			wndCanvansPanelSlot->SetPosition(PrevClosedWndPosition[wndClass->GetName()]);
		}
	}

	// �Է� ���� Ŀ�� ǥ�� ���θ� ������
	if (changeInputMode != EInputModeType::IM_Default)
		PlayerController->SetInputModeFromNewInputModeType(changeInputMode);

	PlayerController->bShowMouseCursor = bShowMouseCursor;

	// ������ â ��ü�� ��ȯ��
	return newClosableWnd;
}

void UWidgetControllerWidget::CloseWnd(bool bAllClose, UClosableWnd* closableWndInstanceToClose)
{
	// ���� ���� â�� �������� ���� ��� �������� ����
	if (AllocatedWnds.Num() == 0)
		return;

	// ��� â�� �ݵ��� �Ͽ��ٸ�
	if (bAllClose)
	{
		for (auto wnd : AllocatedWnds)
		{
			// ���� ó���� â�̶�� �������� ����
			if (wnd->bBeClose)
				continue;

			wnd->bBeClose = true;

			// â ���� �̺�Ʈ�� �߻���Ŵ - Multicast
			if (wnd->OnWndClosedEvent.IsBound())
				wnd->OnWndClosedEvent.Broadcast(wnd);

			// ��� �ڽ� â�� ����
			wnd->CloseAllChildWnd();

			// â ��ġ�� ������
			SaveWndPosition(wnd);

			// �θ� â���� ���
			wnd->DetachFromParent();

			// CanvasPanel_WndParent ������ �ڽĿ��� ������
			CanvasPanel_WndParent->RemoveChild(wnd);
		}

		// �Ҵ�� â �迭�� ���
		AllocatedWnds.Empty();
	}

	// Ư���� â�� �ݵ��� �Ͽ��ٸ�
	{
		// ���� â�� �������� �ʾѵ��� ���������� ���� â�� ���� â���� ������
		closableWndInstanceToClose = (closableWndInstanceToClose != nullptr) ?
			closableWndInstanceToClose :
			AllocatedWnds[AllocatedWnds.Num() - 1];

		// �� ���� â�� �ƴ϶��
		if (!closableWndInstanceToClose->bBeClose)
		{
			// ���� â���� ������
			closableWndInstanceToClose->bBeClose = true;
			
			// â ���� �̺�Ʈ�� �߻���Ŵ
			if (closableWndInstanceToClose->OnWndClosedEvent.IsBound())
				closableWndInstanceToClose->OnWndClosedEvent.Broadcast(closableWndInstanceToClose);

			// ��� �ڽ� â�� ������
			closableWndInstanceToClose->CloseAllChildWnd();

			// �Ҵ�� â �迭���� ������
			AllocatedWnds.Remove(closableWndInstanceToClose);

			// â ��ġ�� ������
			SaveWndPosition(closableWndInstanceToClose);

			// �θ� â���� ���
			closableWndInstanceToClose->DetachFromParent();

			// CanvasPanel_WndParent ������ �ڽĿ��� ������
			CanvasPanel_WndParent->RemoveChild(closableWndInstanceToClose);
		}
	}

	// �Է� ��� �ʱ�ȭ
	ResetInputMode();
}

void UWidgetControllerWidget::AddChildWidget(UUserWidget* childWidgetInstance, EInputModeType changeInputMode,
	bool bShowMouseCursor, float width, float height)
{
	if (childWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetContollerWidget.cpp :: %d LINE :: childWidgetInstance is nullptr"), __LINE__);

		return;
	}

	CanvasPanel_WidgetParent->AddChild(childWidgetInstance);
	/// - Widget->AddChild(childWidget) : childWidet �� Widget �� ������ �߰���

	Cast<UCanvasPanelSlot>(childWidgetInstance->Slot)->SetSize(FVector2D(width, height));

	// �Է� ���� Ŀ�� ���ü��� ������
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMouseCursor;

	AllocatedWidgets.Add(childWidgetInstance);
}

void UWidgetControllerWidget::CloseChildWidget(UUserWidget* childWidgetInstance)
{
	if (childWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetContollerWidget.cpp :: %d LINE :: childWidgetInstance is nullptr"), __LINE__);

		return;
	}

	// �����Ϸ��� ������ AllocatedWidgets ���� ������
	AllocatedWidgets.Remove(childWidgetInstance);

	// �����Ϸ��� ������ ȭ�鿡�� ���
	CanvasPanel_WidgetParent->RemoveChild(childWidgetInstance);
	/// - �θ� �������� �ڽ� ������ ������

	// childWidgetInstance->RemoveFromParent();
	/// - �ڽ� �������� �θ�� ������ ����

	// �Է� ��带 �⺻ ������ ������
	ResetInputMode();
}

void UWidgetControllerWidget::SetHighestPriorityWnd(UClosableWnd* closableWndInstance)
{
	// �켱������ �����ų ������ ������ ����
	UCanvasPanelSlot* wndSlot = closableWndInstance->GetCanvasPanelSlot();

	// �ֻ������ �����Ϸ��� ������ �ֻ�ܿ� ��ġ�Ǿ� ���� �ʴٸ�
	if (CanvasPanel_WndParent->GetChildIndex(closableWndInstance) !=
		CanvasPanel_WndParent->GetSlots().Num() - 1)
		// GetChildIndex(widget) : widget �� ���� ���� ������ ��ȯ��
		// GetSlots() : �߰��� �������� ���� ������ �����ϴ� �迭�� ��ȯ��
	{
		// ��ġ, Anchor, Allignment �� ������
		FVector2D prevPosition = wndSlot->GetPosition();
		FAnchors prevAnchors = wndSlot->GetAnchors();
		FVector2D prevAllignment = wndSlot->GetAlignment();

		// ������ ������
		CanvasPanel_WndParent->AddChild(closableWndInstance);

		// Anchor, Alignment, ��ġ, ũ�⸦ �缳����
		wndSlot = closableWndInstance->GetCanvasPanelSlot();
		wndSlot->SetAnchors(prevAnchors);
		wndSlot->SetAlignment(prevAllignment);
		wndSlot->SetPosition(prevPosition);
		wndSlot->SetSize(closableWndInstance->GetWndSize());
	}
}

void UWidgetControllerWidget::SortGridPanelElem(UUserWidget* gridPanelElem, int maxColumnCount,
	int& refCurrentColumnCount)
{
	UGridSlot* gridSlot = Cast<UGridSlot>(gridPanelElem->Slot);

	if (!IsValid(gridSlot))
		return;

	// �׸��� ��� ���� ������
	gridSlot->SetColumn(refCurrentColumnCount % maxColumnCount);
	gridSlot->SetRow(refCurrentColumnCount / maxColumnCount);
	refCurrentColumnCount++;
}
