// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BaseSlot/ItemSlot/PlayerInventoryItemSlot/PlayerInventoryItemSlot.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/ClosableWnd/PlayerEquipItemWnd/PlayerEquipItemWnd.h"
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

	// 슬롯 타입 설정
	SlotType = ESlotType::ST_InventorySlot;

	// 슬롯 드래그 허용
	bAllowDragOperation = true;

	// 슬롯 드래깅이 시작되었을 경우
	OnSlotDragStarted.AddLambda(
		[this](USlotDragDropOperation* dragDropOperation)
		{
			// 슬롯이 비어있다면 실행 취소
			if (GetItemInfo()->IsEmpty())
				return;

			auto dragWidgetData = CreateSlotDragWidget();
			auto dragWidgetInstance = dragWidgetData.Get<0>();
			auto dragWidgetImage = dragWidgetData.Get<1>();

			// 드래그 시 표시되는 위젯을 설정함
			dragDropOperation->DefaultDragVisual = dragWidgetInstance;

			// 드래그 시 표시되는 이미지를 설정함
			dragWidgetImage->SetBrushFromTexture(
				Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));

			// 슬롯의 아이템 이미지 색상을 드래깅 색상으로 설정함
			SetSlotColorDragging();
		});

	// 슬롯 드래깅이 취소되었을 경우
	OnSlotDragCancelled.AddLambda(
		[this](USlotDragDropOperation* dragDropOperation)
		{
			// 슬롯이 비어잇다면 실행 취소
			if (GetItemInfo()->IsEmpty())
				return;

			// 아이템 이미지 색상을 기본 색상으로 설정함
			SetSlotColorNormal();
		});

	// 슬롯 드래깅이 성공적으로 끝났을 경우
	OnSlotDragFinished.AddLambda(
		[this](USlotDragDropOperation* dragDropOperation)
		{
			if (dragDropOperation->OriginatedDragSlot->GetSlotType() == ESlotType::ST_InventorySlot)
			{
				auto originatedDragSlot = Cast<UPlayerInventoryItemSlot>(dragDropOperation->OriginatedDragSlot);

				// 슬롯이 비어있다면 실행 취소
				if (originatedDragSlot->GetItemInfo()->IsEmpty())
					return;

				// 아이템 이미지 색상을 기본 색상으로 설정함
				dragDropOperation->OriginatedDragSlot->SetSlotColorNormal();

				FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

				// 드래그를 시작시킨 슬롯과 드랍을 시킨 위치의 슬롯에 담긴 아이템이 동일한 아이템을 담고 있는지를 나타냄
				bool bIsSameItem =
					playerInfo->InventoryItemInfos[originatedDragSlot->GetItemSlotIndex()].IsSameItem(
						playerInfo->InventoryItemInfos[GetItemSlotIndex()]);

				// 동일한 아이템이 라면 아이템을 서로 합함
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

	// 우클릭, 좌 더블 클릭 시 장비 아이템을 장착함
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
	Super::InitializeSlot(slotType, itemCode);

	ItemSlotIndex = itemSlotIndex;

	UpdateItemCountText();
}

void UPlayerInventoryItemSlot::UpdateInventoryItemSlot()
{
	UpdateItemImage();
	UpdateItemCountText();
}

void UPlayerInventoryItemSlot::AttachToEquipItemSlot(UPlayerEquipSlot* targetEquipSlot)
{
	// 만약 해당 슬롯에 아이템이 존재하지 않는다면 실행하지 않음
	if (GetItemInfo()->IsEmpty())
		return;

	// 만약 해당 슬롯의 아이템이 장비 아이템이 아니라면 실행하지 않음
	if (GetItemInfo()->ItemType != EItemType::Equipment)
		return;

	// PlayerInventory 객체를 얻음
	UPlayerInventory* playerInventory = GetManager(UPlayerManager)->GetPlayerInventory();

	// 장비 창을 얻음
	UPlayerEquipItemWnd* playerEquipItemWnd = playerInventory->GetPlayerEquipItemWnd();

	// 장비 아이템 정보를 얻음
	FString contextString;
	FEquipItemInfo* equipItemInfo = DT_EquipItemInfo->FindRow<FEquipItemInfo>(
		GetItemInfo()->ItemCode, contextString);

	// 장비 아이템 정보를 얻지 못했다면 실행
	if (equipItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("UPlayerInventoryItemSlot.cpp :: %d LINE :: equipItemInfo is nullptr! (GetItemInfo()->ItemCode is %s)"),
			__LINE__, *GetItemInfo()->ItemCode.ToString());

		return;
	}

	// 장비 아이템 창이 유효한 경우
	if (IsValid(playerEquipItemWnd))
	{
		// targetEquipSlot 이 전달되지 않았다면 장비 아이템 창에서 파츠와 일치하는 슬롯을 찾음
		/// - (더블 클릭이나, 우클릭으로 장비 장착을 실행하는 경우)
		if (targetEquipSlot == nullptr)
			targetEquipSlot = playerEquipItemWnd->GetPlayerEquipSlot(equipItemInfo->PartsType);

		// 장착시키려는 장비 아이템의 파츠 타입을 가질 수 있는 장비 아이템 슬롯을 찾지 못했다면 실행하지 않음
		if (targetEquipSlot == nullptr)
		{
			UE_LOG(LogTemp, Error,
				TEXT("UPlayerInventoryItemSlot.cpp :: %d LINE :: targetEquipSlot is nullptr (equipItemInfo->PartsType is %d)"),
				__LINE__, static_cast<uint8>(equipItemInfo->PartsType));

			return;
		}
		// 장착시키려는 아이템의 타입과 장비 아이템 슬롯 타입이 다를 경우
		else if (targetEquipSlot->GetPartsType() != equipItemInfo->PartsType)
			return;
		
	}

	// 이전에 장착했던 아이템 정보
	FItemSlotInfo prevEquippedItemInfo;

	// 아이템 장착
	playerInventory->EquipItem(GetItemInfo()->ItemCode, &prevEquippedItemInfo);	
	
	// 해당 슬롯을 비움
	playerInventory->RemoveItem(GetItemSlotIndex());

	// 장비창 갱신
	if (IsValid(playerEquipItemWnd))
		playerEquipItemWnd->UpdatePartsSlot();

	// 전에 장착했던 아이템을 인벤토리에 추가함
	playerInventory->AddItem(prevEquippedItemInfo);
}

void UPlayerInventoryItemSlot::UpdateItemCountText()
{
	auto itemSlotInfo = GetManager(UPlayerManager)->GetPlayerInventory()->GetItemSlotInfo(ItemSlotIndex);

	SetSlotItemCount(itemSlotInfo->ItemCount);
}
