// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ClosableWnd/MessageBoxWnd/MessageBoxWnd.h"

#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"
#include "Widget/ClosableWnd/DraggableWndTitle/DraggableWndTitle.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UMessageBoxWnd::SetButtonVisibility(UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility)
{
	ESlateVisibility hide =		ESlateVisibility::Collapsed;
	ESlateVisibility visible =	ESlateVisibility::Visible;

	button->SetVisibility(
		((visibility & (int8)buttonType) == 0) ? hide : visible);
}

void UMessageBoxWnd::InitializeMeesageBox(FText titleText, FText msg, uint8 buttons)
{
	// 창 제목 설정
	SetTitleText(titleText);

	// 메시지 설정
	Text_Message->SetText(msg);

	// 버튼 표시
	SetButtonVisibility(Button_Ok, EMessageBoxButton::MB_Ok, buttons);
	SetButtonVisibility(Button_Cancel, EMessageBoxButton::MB_Cancle, buttons);
}

void UMessageBoxWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// 창 크기 설정
	WndSize = FVector2D(500.0f, 300.0f);

	Button_Ok->OnClicked.AddDynamic(this, &UMessageBoxWnd::OnOkButtonClikced);
	Button_Cancel->OnClicked.AddDynamic(this, &UMessageBoxWnd::OnCancelButtonClicked);
}

void UMessageBoxWnd::CloseThisWnd()
{
	if (IsValid(MsgBoxBackground))
	{
		MsgBoxBackground->RemoveFromParent();
		MsgBoxBackground = nullptr;
	}

	Super::CloseThisWnd();
}

void UMessageBoxWnd::OnOkButtonClikced()
{
	OnOkButtonClickedEvent.ExecuteIfBound(WidgetController, this);
}

void UMessageBoxWnd::OnCancelButtonClicked()
{
	OnCancelButtonClickedEvent.ExecuteIfBound(WidgetController, this);
}
