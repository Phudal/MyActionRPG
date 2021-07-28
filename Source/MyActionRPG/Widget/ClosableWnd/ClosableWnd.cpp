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

	// 창 크기를 설정함
	WndSize = FVector2D(500.0f, 600.0f);

	BP_DraggableWndTitle->SetTargetWidget(this);

	// 드래깅이 시작될 때 이 창을 최상단으로 배치
	//BP_DraggableWndTitle->OnDraggingStarted.AddLambda(
	//[this](){WidgetController->})

	SetCloseButton(BP_DraggableWndTitle->GetCloseButton());
}

void UClosableWnd::SetCloseButton(UButton* closeButton)
{
	(CloseButton = closeButton)->OnClicked.AddDynamic(this, &UClosableWnd::CloseThisWnd);
}

//UClosableWnd* UClosableWnd::CreateChildClosableWnd(TSubclassOf<UClosableWnd> closableWndClass, bool bUsePrevPosition,
//	EInputModeType changeInputMode, bool bShowMouseCursor)
//{
//	// 자식 창을 생성함
//	// auto childWnd = WidgetController->CreateWns
//
//	return closableWndClass;
//}

void UClosableWnd::CloseThisWnd()
{
}

void UClosableWnd::CloseAllChildWnd()
{
}

void UClosableWnd::DetachFromParent()
{
}

UCanvasPanelSlot* UClosableWnd::GetCanvasPanelSlot() const
{
	return Cast<UCanvasPanelSlot>(Slot);
}

void UClosableWnd::SetTitleText(FText newTitleText)
{
	
}