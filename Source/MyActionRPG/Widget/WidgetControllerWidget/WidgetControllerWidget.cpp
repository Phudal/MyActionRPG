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
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/MessageBoxWnd/BP_MessageMessageBoxWnd_C'"));

	if (BP_MESSAGE_BOX_WND.Succeeded())
		BP_MessageBoxWnd = BP_MESSAGE_BOX_WND.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> BP_MESSAGE_BOX_BACKGROUND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/MessageBoxWnd/BP_MessageBoxBackground_C'"));

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
}

void UWidgetControllerWidget::AddChildWidget(UUserWidget* childWidgetInstance, EInputModeType changeInputMode,
	bool bShowMouseCursor, float width, float height)
{
}

void UWidgetControllerWidget::CloseChildWidget(UUserWidget* childWidgetInstance)
{
}

void UWidgetControllerWidget::SetHighestPriorityWnd(UClosableWnd* closableWndInstance)
{
}

void UWidgetControllerWidget::SortGridPanelElem(UUserWidget* gridPanelElem, int maxColumnCount,
	int& refCurrentColumnCount)
{
}
