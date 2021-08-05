// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Struct/ItemSlotInfo/ItemSlotInfo.h"
#include "UObject/NoExportTypes.h"

#include "Enum/InputModeType.h"
#include "Enum/PartsType.h"

#include "PlayerInventory.generated.h"

#ifndef ITEM_ALL
#define ITEM_ALL -1
#endif


UCLASS()
class MYACTIONRPG_API UPlayerInventory : public UObject
{
	GENERATED_BODY()

private:
	TSubclassOf<class UPlayerInventoryWnd> BP_PlayerInventoryWnd;

	TSubclassOf<class UPlayerEquipItemWnd> BP_EquipItemWnd;

	class UDataTable* DT_EquipItemInfo;

private:
	UPROPERTY()
	class UPlayerInventoryWnd* PlayerInventoryWnd;

	UPROPERTY()
	class UPlayerEquipItemWnd* PlayerEquipItemWnd;

public:
	UPlayerInventory();	

	
public:
	// 인벤토리 창을 생성함
	class UPlayerInventoryWnd* CreateInventoryWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, 
		bool bShowCursor = true);

	// 장비 아이템 창을 생성함
	class UPlayerEquipItemWnd* CreateEquipItemWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default,
		bool bShowCursor = true);

	// 인벤토리 창을 닫음
	void CloseInventoryWnd();

	// 장비 아이템 창을 닫음
	void CloseEquipItemWnd();

	// 인벤토리 창을 토글함
	void ToggleInventoryWnd(class UWidgetControllerWidget* widgetController, bool bOpenEquipItemWnd = false);

	// 장비 창을 토글함
	void ToggleEquipItemWnd(class UWidgetControllerWidget* widgetController);
	
	// 아이템 슬롯 정보를 얻음
	FItemSlotInfo* GetItemSlotInfo(int32 slotIndex) const;
	
	// 인벤토리 아이템 교체
	void SwapItem(class UPlayerInventoryItemSlot* first, class UPlayerInventoryItemSlot* second);

	// 아이템을 인벤토리에 추가함
	bool AddItem(FItemSlotInfo& newItemSlotInfo);
	
	// 동일한 아이템을 합침
	void MergeItem(class UPlayerInventoryItemSlot* ori, class UPlayerInventoryItemSlot* target);

	// 아이템을 인벤토리에서 제거함
	/// - itemSlotIndex : 제거할 슬롯 인덱스를 전달함
	/// - removeCoutn : 제거할 개수
	///   ITEM_ALL이 전달된다면 모든 아이템을 제거
	void RemoveItem(int32 itemSlotIndex, int32 removeCount = ITEM_ALL);

	// 장비 아이템을 장착함
	/// - equipItemCode : 장착하려는 아이템 코드를 전달함
	/// - out_PrevItemSlotInfo: 이전에 장착한 아이템 정보를 받을 ItemSlotInfo 변수를 전달
	void EquipItem(FName equipItemCode, FItemSlotInfo* out_PrevItemSlotInfo = nullptr);
	

	// 장비 아이템을 장착 해제함
	/// - partsType : 장착 해제하려는 파츠를 전달함
	/// - out_ItemSlotInfo : 이전에 장착한 아이템 정보를 담은 ItemSlotInfo 변수를 전달함
	void DismountItem(EPartsType partsType, FItemSlotInfo* out_ItemSlotInfo = nullptr);

	// 플레이어 캐릭터의 비쥬얼을 갱신함
	/// - 모든 Mesh가 갱신됨
	void UpdateCharacterVisual();

	// 플레이어 캐릭터 비쥬얼을 갱신함
	/// - updateParts : 갱신시킬 파츠를 전달함
	/// - equipItemInfo : 장비 아이템 정보를 전달함
	///   - 만약 nullptr 를 전달한다면 이 메서드 내에서 캐릭터에 장착된 장비 정보를 이용하여 데이터를 얻음
	void UpdateCharacterVisual(EPartsType updateParts, struct FEquipItemInfo* equipItemInfo = nullptr);
	
public:
	FORCEINLINE class UPlayerInventoryWnd* GetPlayerInventoryWnd() const
	{
		return PlayerInventoryWnd;
	}

	FORCEINLINE class UPlayerEquipItemWnd* GetPlayerEquipItemWnd() const
	{
		return PlayerEquipItemWnd;
	}
};
