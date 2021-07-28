// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Enum/MessageBoxButton.h"

#include "MessageBoxWnd.generated.h"


DECLARE_DELEGATE_TwoParams(FOnButtonEventSignature, class UWidgetControllerWidget *, class UMessageBoxWnd*)
 
UCLASS()
class MYACTIONRPG_API UMessageBoxWnd : public UClosableWnd
{
	GENERATED_BODY()

public:
	// ok 버튼이 클릭되었을 때 호출되는 대리자
	FOnButtonEventSignature OnOkButtonClickedEvent;

	// cancel 버튼이 클릭되었을 때 호출되는 대리자
	FOnButtonEventSignature OnCancelButtonClickedEvent;

public:
	// 함께 사용되는 배경 위젯을 나타냄
	UPROPERTY()
	class UUserWidget* MsgBoxBackground;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Message;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Ok;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Cancel;

private:
	// 버튼의 가시성을 설정함
	/// - button : 설정할 버튼을 전달함
	/// - buttonType : 버튼의 타임을 전달함
	/// - visibility : 표시 여부를 나타내는 데이터를 전달함
	void SetButtonVisibility(class UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility);

public:
	// 메시지 박스를 초기화함
	/// - titleText : 메시지 박스의 타이틀 문자열을 전달함
	/// - msg : 표시할 메시지 문자열을 전달함
	/// - buttons : 표시할 버튼을 비트연산자 OR 연산자와 함께 전달함
	void InitializeMeesageBox(FText titleText, FText msg, uint8 buttons);
	
protected:
	virtual void NativeConstruct() override;

public:
	virtual void CloseThisWnd() override;

private:
	UFUNCTION()
	void OnOkButtonClikced();

	UFUNCTION()
	void OnCancelButtonClicked();	
};
