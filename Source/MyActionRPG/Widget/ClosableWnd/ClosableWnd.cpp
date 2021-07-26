// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Components/CanvasPanelSlot.h"

#include "Widget/ClosableWnd/ClosableWnd.h"
#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/Button.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// 창 크기를 설정함
	WndSize = FVector2D(500.0f, 600.0f);

	// BP_Dra
}

void UClosableWnd::SetCloseButton(UButton* closeButton)
{
}

UClosableWnd* UClosableWnd::CreateChildClosableWnd(TSubclassOf<UClosableWnd> closableWndClass, bool bUsePrevPosition,
	EInputModeType changeInputMode, bool bShowMouseCursor)
{
}

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
}

void UClosableWnd::SetTitleText(FText newTitleText)
{
	
}