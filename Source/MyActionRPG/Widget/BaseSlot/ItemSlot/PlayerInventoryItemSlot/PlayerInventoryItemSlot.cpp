// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BaseSlot/ItemSlot/PlayerInventoryItemSlot/PlayerInventoryItemSlot.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/ClosableWnd/PlayerEquipmentWnd/PlayerEquipmentWnd.h"
#include "Widget/BaseSlot/ItemSlot/PlayerEquipSlot/PlayerEquipSlot.h"

#include "Struct/EquipItemInfo/EquipItemInfo.h"

#include "Components/Image.h"

UPlayerInventoryItemSlot::UPlayerInventoryItemSlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EQUIP_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_EquipItemInfo.DT_EquipItemInfo'"));

	if (DT_EQUIP_ITEM_INFO.Succeeded())
		DT_EquipItemInfo = DT_EQUIP_ITEM_INFO.Object;
}

void UPlayerInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� Ÿ�� ����
	SlotType = ESlotType::ST_InventorySlot;

	// ���� �巡�� ���
	bAllowDragOperation = true;

	// ���� �巡���� ���۵Ǿ��� ���
	OnSlotDragStarted.AddLambda(
		[this](USlotDragDropOperation* dragDropOperation)
		{
			// ������ ����ִٸ� ���� ���
			if (GetItemInfo()->IsEmpty())
				return;

			auto dragWidgetData = CreateSlotDragImage();
			auto dragWidgetInstance = dragWidgetData.Get<0>();
			auto dragWidgetImage = dragWidgetData.Get<1>();

			// �巡�� �� ǥ�õǴ� ������ ������
			dragDropOperation->DefaultDragVisual = dragWidgetInstance;

			// �巡�� �� ǥ�õǴ� �̹����� ������
			dragWidgetImage->SetBrushFromTexture(
				Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));

			// ������ ������ �̹��� ������ �巡�� �������� ������
			SetSlotColorDragging();
		});

	// ���� �巡���� ��ҵǾ��� ���
	OnSlotDragCancelled.AddLambda(
		[this](USlotDragDropOperation* dragDropOperation)
		{
			// ������ ����մٸ� ���� ���
			if (GetItemInfo()->IsEmpty())
				return;

			// ������ �̹��� ������ �⺻ �������� ������
			SetSlotColorNormal();
		});

	// ���� �巡���� ���������� ������ ���
	OnSlotDragFinished.AddLambda(
		[this](USlotDragDropOperation* dragDropOperation)
		{
			if (dragDropOperation->OriginatedDragSlot->GetSlotType() == ESlotType::ST_InventorySlot)
			{
				auto originatedDragSlot = Cast<UPlayerInventoryItemSlot>(dragDropOperation->OriginatedDragSlot);

				// ������ ����ִٸ� ���� ���
				if (originatedDragSlot->GetItemInfo()->IsEmpty())
					return;

				// ������ �̹��� ������ �⺻ �������� ������
				dragDropOperation->OriginatedDragSlot->SetSlotColorNormal();

				FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

				// �巡�׸� ���۽�Ų ���԰� ����� ��Ų ��ġ�� ���Կ� ��� �������� ������ �������� ��� �ִ����� ��Ÿ��
				bool bIsSameItem =
					playerInfo->InventoryItemInfos[originatedDragSlot->GetItemSlotIndex()].IsSameItem(
						playerInfo->InventoryItemInfos[GetItemSlotIndex()]);

				// ������ �������� ��� �������� ���� ����
				if (bIsSameItem)
					GetManager(UPlayerManager)->GetPlayerInventory()->MergeItem(originatedDragSlot, this);

				else
					GetManager(UPlayerManager)->GetPlayerInventory()->SwapItem(originatedDragSlot, this);
			}

			else if (dragDropOperation->OriginatedDragSlot->GetSlotType() == ESlotType::ST_EquipSlot)
			{
				auto originatedDragSlot = Cast<UPlayerEquipSlot>(dragDropOperation->OriginatedDragSlot);

				originatedDragSlot->SetSlotColorNormal();

				originatedDragSlot->DetachToEquipItemSlot(ItemSlotIndex);
			}
		});

	// ��Ŭ��, �� ���� Ŭ�� �� ��� �������� ������
	OnMouseRightButtonClicked.AddLambda(
		[this](ESlotType slotType)
		{
			AttachToEquipItemSlot();
		});

	OnMouseLeftButtonDBClicked.AddLambda(
		[this](ESlotType slotType)
		{
			AttachToEquipItemSlot();
		});
}

void UPlayerInventoryItemSlot::InitializeItemSlot(ESlotType slotType, FName itemCode, int32 itemSlotIndex)
{
}

void UPlayerInventoryItemSlot::UpdateInventoryItemSlot()
{
}

void UPlayerInventoryItemSlot::AttachToEquipItemSlot(UPlayerEquipSlot*)
{
}

void UPlayerInventoryItemSlot::UpdateItemCountText()
{
}
