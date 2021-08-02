// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BaseSlot/ItemSlot/ItemSlot.h"
#include "PlayerEquipSlot.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API UPlayerEquipSlot : public UItemSlot
{
	GENERATED_BODY()

public:
	// 장비 아이템 장착 해제
	/// - inventorySlotIndex : 장착중읻너 장비 아이템을 어느 인벤토리 슬롯에 추가할 것인지를 지정함
	void DetachToEquipItemSlot(int32 inventorySlotIndex = INDEX_NONE);
};
