// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API UPlayerInventory : public UObject
{
	GENERATED_BODY()

public:
	// 인벤토리 아이템 교체
	void SwapItem(class UPlayerInventoryItemSlot* first, class UPlayerInventoryItemSlot* second);

	// 동일한 아이템을 합침
	void MergeItem(class UPlayerInventoryItemSlot* ori, class UPlayerInventoryItemSlot* target);
};
