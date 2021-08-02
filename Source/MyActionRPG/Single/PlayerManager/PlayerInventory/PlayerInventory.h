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
	// �κ��丮 ������ ��ü
	void SwapItem(class UPlayerInventoryItemSlot* first, class UPlayerInventoryItemSlot* second);

	// ������ �������� ��ħ
	void MergeItem(class UPlayerInventoryItemSlot* ori, class UPlayerInventoryItemSlot* target);
};
