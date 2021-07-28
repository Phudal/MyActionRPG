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
	// ok ��ư�� Ŭ���Ǿ��� �� ȣ��Ǵ� �븮��
	FOnButtonEventSignature OnOkButtonClickedEvent;

	// cancel ��ư�� Ŭ���Ǿ��� �� ȣ��Ǵ� �븮��
	FOnButtonEventSignature OnCancelButtonClickedEvent;

public:
	// �Բ� ���Ǵ� ��� ������ ��Ÿ��
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
	// ��ư�� ���ü��� ������
	/// - button : ������ ��ư�� ������
	/// - buttonType : ��ư�� Ÿ���� ������
	/// - visibility : ǥ�� ���θ� ��Ÿ���� �����͸� ������
	void SetButtonVisibility(class UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility);

public:
	// �޽��� �ڽ��� �ʱ�ȭ��
	/// - titleText : �޽��� �ڽ��� Ÿ��Ʋ ���ڿ��� ������
	/// - msg : ǥ���� �޽��� ���ڿ��� ������
	/// - buttons : ǥ���� ��ư�� ��Ʈ������ OR �����ڿ� �Բ� ������
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
