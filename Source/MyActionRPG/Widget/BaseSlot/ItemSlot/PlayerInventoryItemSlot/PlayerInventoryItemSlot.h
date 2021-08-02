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
	// �κ��丮 ���� �ε����� ��Ÿ��
	int32 ItemSlotIndex;

public:
	UPlayerInventoryItemSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	
public:
	void InitializeItemSlot(ESlotType slotType, FName itemCode, int32 itemSlotIndex);

	// ������ ������ ������
	void UpdateInventoryItemSlot();

	// ��� �������� ������
	void AttachToEquipItemSlot(class UPlayerEquipSlot* = nullptr);

private:
	// ������ ���� �ؽ�Ʈ�� ������
	void UpdateItemCountText();

public:
	FORCEINLINE int32 GetItemSlotIndex() const
	{
		return ItemSlotIndex;
	}
};
