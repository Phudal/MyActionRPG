// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Blueprint/UserWidget.h"

#include "Enum/SlotType.h"

#include "Widget/BaseSlot/SlotDragDropOperation/SlotDragDropOperation.h"

#include "BaseSlot.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FSlotMouseEventSignature, ESlotType)
DECLARE_MULTICAST_DELEGATE_OneParam(FSlotDragEventSignature, class USlotDragDropOperation*)

UCLASS()
class MYACTIONRPG_API UBaseSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	// ���콺 ���� Ŭ�� �� ȣ��Ǵ� �븮��
	FSlotMouseEventSignature OnMouseLeftButtonClicked;

	// ���콺 ���� ���� Ŭ�� �� ȣ��Ǵ� �븮��
	FSlotMouseEventSignature OnMouseLeftButtonDBClicked;

	// ���콺 ������ ��ư Ŭ�� �� ȣ��Ǵ� �븮��
	FSlotMouseEventSignature OnMouseRightButtonClicked;

	// ���� �巡�� ���� �� ȣ��Ǵ� �븮��
	FSlotDragEventSignature OnSlotDragStarted;

	// �巡�� ��� �� ȣ��Ǵ� �븮��
	FSlotDragEventSignature OnSlotDragFinished;

	// �巡�� ��� �� ȣ��Ǵ� �븮��
	FSlotDragEventSignature OnSlotDragCancelled;

private:
	// ���� �巡�� �� �����Ǵ� ���� �������Ʈ UClass
	TSubclassOf<UUserWidget> BP_SlotDragImage;

protected:
	class UTexture2D* T_Null;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ItemCount;

protected:
	UPROPERTY()
	ESlotType SlotType;

	// ������ ���԰� �Բ� ���Ǵ� �ڵ带 ��Ÿ��
	/// - ex) ������ �ڵ�, ��ų �ڵ�
	FName InCode;

	// �巡�� �۾��� ����� �������� ��Ÿ��
	bool bAllowDragOperation;

public:
	UBaseSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	// �� ������ ���콺 ��ħ�� ���۵Ǿ��� �� ȣ��Ǵ� �޼���
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// �� ������ ���콺 ��ħ�� ������ ��� ȣ��Ǵ� �޼���
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override final;

	// �ش� ������ ���콺 Ŭ�� �Է��� ���� ��� ȣ��
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;
	/// - FReply : �̺�Ʈ�� ��� ������� ó���Ǿ��� �� �˸��� ���� ����
	/// - InGeometry : ������ ��ġ, ũ�⸦ ��Ÿ��
	/// - InMouseEvent : ���콺 �Է� �̺�Ʈ�� ����

	// ���콺 Ŭ�� �Է��� ���� ��� ȣ���
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// �� ������ ���� Ŭ���Ǿ��� ��� ȣ���
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// �ش� ������ �巡�� �̺�Ʈ�� �߻����� ��� ȣ���
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override final;

	// �巡�װ� ������ ��� ȣ��Ǵ� �޼���
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override final;

public:
	// ������ �ʱ�ȭ��
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

	// ���Կ� ǥ�õǴ� ���ڸ� ������
	/// - itemCount : ǥ�ý�ų ������ ������ ������
	/// - bVisible01Count : 0 �̳� 1 �� ��쿡�� ǥ���� �������� ������
	void SetSlotItemCount(int32 itemCount, bool bVisible01Count = false);

private:
	// ���� ����� �⺻ �������� ǥ����
	void ShowSlotNormalSlate();

	// ���� ����� ���콺 ��ħ ���·� ǥ����
	void ShowSlotHorverState();

	// ���� ����� ���� ���·� ǥ����
	void ShowSlotPressedState();

public:
	// ���� �̹��� ������ �⺻ / �巡�� �������� ������
	void SetSlotColorNormal();
	void SetSlotColorDragging();

protected:
	 TTuple<UUserWidget*, class UImage*> CreateSlotDragWidget();
	/// - Ʃ��
	/// - ������ �̸��� ������ �ʰ�, ���� �ʵ带 ���� �� �ִ� ����ü
	/// - ���� Ʃ���� �������α׷� ��ü���� ����� ������ ������ ���� �ƴ�,
	///   �Ͻ������� ����� ���� ������ ������ ������ �� �����
	/// - �𸮾󿡼� TTuple<Type..> �������� ������ �� ������, MakeTuple() �� ���� �ϳ��� �����͸� ������ �� ����
	/// - ������ Ʃ���� �ʵ忡�� Get<index>()�� ������ �� ����

public:
	FORCEINLINE class UImage* GetSlotBackgruondImage() const
	{
		return Image_SlotBackground;
	}

	FORCEINLINE class UImage* GetSlotImage() const
	{
		return Image_Slot;
	}

	FORCEINLINE ESlotType GetSlotType() const
	{
		return SlotType;
	}
};
