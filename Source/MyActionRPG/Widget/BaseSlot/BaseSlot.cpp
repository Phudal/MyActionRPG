// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BaseSlot/BaseSlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UBaseSlot::UBaseSlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_SLOT_DRAG_IMAGE(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Slot/SlotDragImage/BP_SlotDragImage.BP_SlotDragImage_C'"));

	if (BP_SLOT_DRAG_IMAGE.Succeeded())
		BP_SlotDragImage = BP_SLOT_DRAG_IMAGE.Class;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_NULL(
		TEXT("Texture2D'/Game/Resources/Image/Props/T_NULL.T_NULL'"));

	if (T_NULL.Succeeded())
		T_Null = T_NULL.Object;

	// 기본적으로 드래깅을 허용하지 않도록 함
	bAllowDragOperation = false;
}

void UBaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 개수가 표시되지 않도록 함
	SetSlotItemCount(0);
}

void UBaseSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	// 슬롯을 마우스 겹침 상태로 표시함
	ShowSlotHorverState();
}

void UBaseSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	// 슬롯을 기본 상태로 표시함
	ShowSlotNormalSlate();
}

FReply UBaseSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto retVal = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 입력된 마우스 버튼을 확인
	return retVal;
}

//FReply UBaseSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//}
//
//FReply UBaseSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//}

void UBaseSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
}

bool UBaseSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return true;
}

void UBaseSlot::InitializeSlot(ESlotType slotTpye, FName inCode)
{
}

void UBaseSlot::SetSlotItemCount(int32 itemCount, bool bVisible01Count)
{
}

void UBaseSlot::ShowSlotNormalSlate()
{
}

void UBaseSlot::ShowSlotHorverState()
{
}

void UBaseSlot::ShowSlotPressedState()
{
}

void UBaseSlot::SetSlotColorNormal()
{
}

void UBaseSlot::SetSlotColorDragging()
{
}

//TTuple<UUserWidget*, UImage*> UBaseSlot::CreateSlotDragImage()
//{
//}
