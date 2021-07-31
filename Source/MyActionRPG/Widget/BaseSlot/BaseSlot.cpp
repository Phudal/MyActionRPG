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

	// �⺻������ �巡���� ������� �ʵ��� ��
	bAllowDragOperation = false;
}

void UBaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// ������ ǥ�õ��� �ʵ��� ��
	SetSlotItemCount(0);
}

void UBaseSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	// ������ ���콺 ��ħ ���·� ǥ����
	ShowSlotHorverState();
}

void UBaseSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	// ������ �⺻ ���·� ǥ����
	ShowSlotNormalSlate();
}

FReply UBaseSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto retVal = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// �Էµ� ���콺 ��ư�� Ȯ��
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
