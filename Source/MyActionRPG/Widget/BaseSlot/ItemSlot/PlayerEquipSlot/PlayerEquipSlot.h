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
	// ��� ������ ���� ����
	/// - inventorySlotIndex : �����ߟ޳� ��� �������� ��� �κ��丮 ���Կ� �߰��� �������� ������
	void DetachToEquipItemSlot(int32 inventorySlotIndex = INDEX_NONE);
};
