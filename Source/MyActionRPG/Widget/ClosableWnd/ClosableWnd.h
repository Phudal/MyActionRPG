// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/InputModeType.h"
#include "ClosableWnd.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FWndEventSigature, class UClosableWnd*)

UCLASS()
class MYACTIONRPG_API UClosableWnd : public UUserWidget
{
	GENERATED_BODY()

public:
	class UWidgetControllerWidget* WigetController;

	// â�� ���� �� ȣ��Ǵ� �븮��
	FWndEventSigature OnWndClosedEvent;

	// �θ� â�� ��Ÿ��
	/// - �θ� â�� nullptr�� �ƴ϶�� �θ� â�� ���� �� �ش� â�� ������ ��
	UPROPERTY()
	UClosableWnd* ParentWnd;

	// �ڽ� â ��ü���� ������
	TArray<UClosableWnd*> ChildWnds;

	// ���� ó���� â���� ��Ÿ��
	UPROPERTY()
	bool bBeClose;

//private:
	//UPROPERTY(meta = (BindWidget))
	//class UDraggableWndTitle* BP_DraggableWndTitle;

protected:
	UPROPERTY()
	class UButton* CloseButton;

	// â ũ�⸦ ��Ÿ��
	FVector2D WndSize;

protected:
	virtual void NativeConstruct() override;

public:
	// �ݱ� ��ư�� ������
	void SetCloseButton(class UButton* closeButton);

	// �ڽ� â�� �����մϴ�.
	/// - closableWndClass : ������ â Ŭ������ �����մϴ�.
	/// - bUsePrevPosition : ���� â ��ġ ��� ���θ� �����մϴ�.
	/// - changeInputMode : �����ų �Է� ��带 �����մϴ�.
	/// - bShowMouseCursor : Ŀ�� ǥ�� ���θ� �����մϴ�.
	/// - return : ������ â�� ��ȯ�˴ϴ�.
	UClosableWnd* CreateChildClosableWnd(
		TSubclassOf<UClosableWnd> closableWndClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_Default,
		bool bShowMouseCursor = true);

	// �� â�� ����
	UFUNCTION()
	virtual void CloseThisWnd();

	// ��� �ڽ� â�� ����
	void CloseAllChildWnd();

	// �θ� â���� ���
	void DetachFromParent();

public:
	// �� â�� CanvasPanelSlot �� ����
	class UCanvasPanelSlot* GetCanvasPanelSlot() const;

	// â�� ũ�⸦ ��ȯ
	FORCEINLINE FVector2D GetWndSize() const
	{
		return WndSize;
	}

	// â�� ������ ������
	void SetTitleText(FText newTitleText);
	
	FORCEINLINE void SetTitleText(FString newTitleText)
	{
		SetTitleText(FText::FromString(newTitleText));
	}
};
