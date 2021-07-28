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
	// 열린 창과 위젯이 존재하지 않는다면 입력 모드를 변경함
	if (bForceChange ||
		((AllocatedWnds.Num() == 0) && (AllocatedWidgets.Num() == 0)))
	{
		// 입력 모드를 설정
		PlayerController->ChangeInputModeToDefault();

		// 커서 표시
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
	// 새로운 창 위젯을 생성함
	UClosableWnd* newClosableWnd = CreateWidget<UClosableWnd>(this, wndClass);
	newClosableWnd->WidgetController = this;

	// 할당된 창 배열에 추가
	AllocatedWnds.Add(newClosableWnd);

	// CanvasPanel_WndParent 의 자식 위젯으로 추가함
	CanvasPanel_WndParent->AddChild(newClosableWnd);

	// Anchor / Alignment 설정
	auto wndCanvansPanelSlot = newClosableWnd->GetCanvasPanelSlot();
	wndCanvansPanelSlot->SetAnchors(FAnchors(anchorMinX, anchorMinY, anchorMaxX, anchorMaxY));
	wndCanvansPanelSlot->SetAlignment(FVector2D(alignmentX, alignmentY));

	// 창 크기를 설정함
	wndCanvansPanelSlot->SetSize(newClosableWnd->GetWndSize());

	// 이전 창 위치를 사용한다면
	if (bUsePrevPosition)
	{
		// 이전 창 위치가 기록되어 있는지 확인함
		if (PrevClosedWndPosition.Contains(wndClass->GetName()))
		{
			// 창 위치를 이전 위치로 설정함
			wndCanvansPanelSlot->SetPosition(PrevClosedWndPosition[wndClass->GetName()]);
		}
	}

	// 입력 모드와 커서 표시 여부를 변경함
	if (changeInputMode != EInputModeType::IM_Default)
		PlayerController->SetInputModeFromNewInputModeType(changeInputMode);

	PlayerController->bShowMouseCursor = bShowMouseCursor;

	// 생성한 창 객체를 반환함
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
