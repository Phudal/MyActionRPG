// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BaseSlot/ItemSlot/ItemSlot.h"
#include "PlayerInventoryItemSlot.generated.h"


UCLASS()
class MYACTIONRPG_API UPlayerInventoryItemSlot : public UItemSlot
{
	GENERATED_BODY()

private:
	class UDataTable* DT_EquipItemInfo;

private:
	// 인벤토리 슬롯 인덱스를 나타냄
	int32 ItemSlotIndex;

public:
	UPlayerInventoryItemSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	
public:
	void InitializeItemSlot(ESlotType slotType, FName itemCode, int32 itemSlotIndex);

	// 아이템 슬롯을 갱신함
	void UpdateInventoryItemSlot();

	// 장비 아이템을 장착함
	void AttachToEquipItemSlot(class UPlayerEquipSlot* = nullptr);

private:
	// 아이템 개수 텍스트를 갱신함
	void UpdateItemCountText();

public:
	FORCEINLINE int32 GetItemSlotIndex() const
	{
		return ItemSlotIndex;
	}
};
