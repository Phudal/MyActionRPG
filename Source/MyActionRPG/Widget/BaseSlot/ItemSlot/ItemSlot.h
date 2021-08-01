// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BaseSlot/BaseSlot.h"
#include "Struct/ItemInfo/ItemInfo.h"
#include "ItemSlot.generated.h"


UCLASS()
class MYACTIONRPG_API UItemSlot : public UBaseSlot
{
	GENERATED_BODY()

private:
	class UDataTable* DT_ItemInfo;

private:
	FItemInfo ItemInfo;

public:
	UItemSlot(const FObjectInitializer& ObjectInitializer);

public:
	virtual void InitializeSlot(ESlotType slotType, FName inCode) override;

	// 아이템 이미지를 갱신함
	void UpdateItemImage();

public:
	void SetItemInfo(FName itemCode);

	FORCEINLINE FItemInfo* GetItemInfo()
	{
		return &ItemInfo;
	}
};
