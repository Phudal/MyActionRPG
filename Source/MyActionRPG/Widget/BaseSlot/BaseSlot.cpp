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
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// ������ ���� ���·� ǥ����
		ShowSlotPressedState();

		// ���� Ŭ�� �̺�Ʈ�� �߻���Ŵ
		if (OnMouseLeftButtonClicked.IsBound())
			OnMouseLeftButtonClicked.Broadcast(SlotType);

		if (bAllowDragOperation)
		{
			// �巡�� �� ��� �۾��� �����ϸ�, �۾� ����� ��ȯ��
			return UWidgetBlueprintLibrary::DetectDragIfPressed(
				InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
			/// - PointEvent : ���콺 �Է� �̺�Ʈ�� ������
			/// - WidgetDetectingDrag : �巡�׸� ������ ��ü
			/// - DragKey : �巡�׸� ������ �� ����� Ű
		}
	}

	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// ������ Ŭ�� �̺�Ʈ�� �߻���Ŵ
		if (OnMouseRightButtonClicked.IsBound())
			OnMouseRightButtonClicked.Broadcast(SlotType);
	}
	
	return retVal;
}

FReply UBaseSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ShowSlotNormalSlate();

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

FReply UBaseSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto retVal = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// ������ �⺻ ���·� ǥ����
		ShowSlotNormalSlate();

		// ���� Ŭ�� �̺�Ʈ �߻�
		if (OnMouseLeftButtonDBClicked.IsBound())
			OnMouseLeftButtonDBClicked.Broadcast(SlotType);

		// ���콺 ���� Ŭ�� �̺�Ʈ�� ó���Ǿ����� �˸�
		return FReply::Handled();
	}

	return retVal;
}

void UBaseSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// ������ �⺻ ���·� ǥ����
	ShowSlotNormalSlate();

	// �巡�� ��� �۾� ��ü�� ������
	USlotDragDropOperation* dragDropOperation = Cast<USlotDragDropOperation>(
		UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDropOperation::StaticClass()));

	// �巡�� ���� ������ ������
	dragDropOperation->OriginatedDragSlot = this;

	// ���� �巡�� ���� �̺�Ʈ �߻�
	if (OnSlotDragStarted.IsBound())
		OnSlotDragStarted.Broadcast(dragDropOperation);

	// ��¿� �Ű� ������ �巡�� �� ��� �۾� ��ü�� ������
	OutOperation = dragDropOperation;
}

bool UBaseSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (OnSlotDragFinished.IsBound())
		OnSlotDragFinished.Broadcast(Cast<USlotDragDropOperation>(InOperation));
	
	return true;
}

void UBaseSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	SlotType = slotType;
	InCode = inCode;
}

void UBaseSlot::SetSlotItemCount(int32 itemCount, bool bVisible01Count)
{
	FText itemCountText = FText::FromString(FString::FromInt(itemCount));

	Text_ItemCount->SetText(
		(!bVisible01Count && itemCount <= 1) ?
		FText() : itemCountText);
}

void UBaseSlot::ShowSlotNormalSlate()
{
	GetSlotBackgruondImage()->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UBaseSlot::ShowSlotHorverState()
{
	GetSlotBackgruondImage()->SetColorAndOpacity(FLinearColor(1.0f, 0.8f, 0.3f));
}

void UBaseSlot::ShowSlotPressedState()
{
	GetSlotBackgruondImage()->SetColorAndOpacity(FLinearColor(0.2f, 0.2f, 0.2f));
}

void UBaseSlot::SetSlotColorNormal()
{
	GetSlotImage()->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UBaseSlot::SetSlotColorDragging()
{
	GetSlotImage()->SetBrushTintColor(FLinearColor(0.2f, 0.2f, 0.2f));
}

TTuple<UUserWidget*, UImage*> UBaseSlot::CreateSlotDragWidget()
{
	// �巡�� �� ��� �� ������ ������ ������
	auto slotDragWidget = CreateWidget<UUserWidget>(this, BP_SlotDragImage);
	auto image_drag = Cast<UImage>(slotDragWidget->GetWidgetFromName(TEXT("Image_Drag")));

	return MakeTuple(slotDragWidget, image_drag);
}
