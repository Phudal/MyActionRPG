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
	// 마우스 왼쪽 클릭 시 호출되는 대리자
	FSlotMouseEventSignature OnMouseLeftButtonClicked;

	// 마우스 왼쪽 더블 클릭 시 호출되는 대리자
	FSlotMouseEventSignature OnMouseLeftButtonDBClicked;

	// 마우스 오른쪽 버튼 클릭 시 호출되는 대리자
	FSlotMouseEventSignature OnMouseRightButtonClicked;

	// 슬롯 드래그 시작 시 호출되는 대리자
	FSlotDragEventSignature OnSlotDragStarted;

	// 드래그 드랍 시 호출되는 대리자
	FSlotDragEventSignature OnSlotDragFinished;

	// 드래그 취소 시 호출되는 대리자
	FSlotDragEventSignature OnSlotDragCancelled;

private:
	// 슬롯 드래그 시 생성되는 위젯 블루프린트 UClass
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

	// 아이템 슬롯과 함께 사용되는 코드를 나타냄
	/// - ex) 아이템 코드, 스킬 코드
	FName InCode;

	// 드래깅 작업을 허용할 것인지를 나타냄
	bool bAllowDragOperation;

public:
	UBaseSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	// 이 위젯과 마우스 겹침이 시작되었을 때 호출되는 메서드
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// 이 위젯과 마우스 겹침이 끝났을 경우 호출되는 메서드
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override final;

	// 해당 위젯에 마우스 클릭 입력이 있을 경우 호출
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;
	/// - FReply : 이벤트가 어떠한 방법으로 처리되었는 지 알리기 위한 형식
	/// - InGeometry : 위젯의 위치, 크기를 나타냄
	/// - InMouseEvent : 마우스 입력 이벤트의 종류

	// 마우스 클릭 입력이 끝날 경우 호출됨
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// 이 위젯이 더블 클릭되었을 경우 호출됨
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// 해당 위젯에 드래그 이벤트가 발생했을 경우 호출됨
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override final;

	// 드래그가 끝났을 경우 호출되는 메서드
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override final;

public:
	// 슬롯을 초기화함
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

	// 슬롯에 표시되는 숫자를 설정함
	/// - itemCount : 표시시킬 아이템 개수를 전달함
	/// - bVisible01Count : 0 이나 1 일 경우에도 표시할 것인지를 전달함
	void SetSlotItemCount(int32 itemCount, bool bVisible01Count = false);

private:
	// 슬롯 배경을 기본 색상으로 표시함
	void ShowSlotNormalSlate();

	// 슬롯 배경을 마우스 겹침 상태로 표시함
	void ShowSlotHorverState();

	// 슬롯 배경을 눌림 상태로 표시함
	void ShowSlotPressedState();

public:
	// 슬롯 이미지 색상을 기본 / 드래깅 색상으로 설정함
	void SetSlotColorNormal();
	void SetSlotColorDragging();

protected:
	 TTuple<UUserWidget*, class UImage*> CreateSlotDragWidget();
	/// - 튜플
	/// - 형식의 이름을 가지지 않고, 여러 필드를 담을 수 있는 구조체
	/// - 보통 튜플은 응용프로그램 전체에서 사용할 형식을 선언할 때가 아닌,
	///   암시적으로 사용할 복합 데이터 형식을 선언할 때 사용함
	/// - 언리얼에서 TTuple<Type..> 형식으로 선언할 수 있으며, MakeTuple() 을 통해 하나의 데이터를 생성할 수 있음
	/// - 생성된 튜플의 필드에는 Get<index>()로 접근할 수 있음

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
