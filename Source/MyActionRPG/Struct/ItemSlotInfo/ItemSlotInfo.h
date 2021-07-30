// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ItemSlotInfo.generated.h"


USTRUCT()
struct MYACTIONRPG_API FItemSlotInfo 
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ �ڵ�
	UPROPERTY()
	FName ItemCode;

	// ������ ����
	UPROPERTY()
	int32 ItemCount;

	// ���Կ� ����� �� �ִ� �ִ� ����
	UPROPERTY()
	int32 MaxSlotCount;

public:
	FItemSlotInfo();
	FItemSlotInfo(FName itemCode, int32 itemCount = 0, int32 maxSlotCount = 0);

	FORCEINLINE bool operator==(const FItemSlotInfo& itemSlotInfo)
	{
		return
			this->ItemCode == itemSlotInfo.ItemCode &&
			this->ItemCount == itemSlotInfo.ItemCount;
	}

	FORCEINLINE bool operator!=(const FItemSlotInfo& itemSlotInfo)
	{
		return
			this->ItemCode != itemSlotInfo.ItemCode ||
			this->ItemCount != itemSlotInfo.ItemCount;
	}

	// ���� ���������� Ȯ��
	FORCEINLINE bool IsSameItem(const FItemSlotInfo& itemSlotInfo) const
	{
		if (itemSlotInfo.IsEmpty())
			return false;

		return (ItemCode == itemSlotInfo.ItemCode);
	}

	// �ش� �����Ͱ� ����ִ��� Ȯ��
	FORCEINLINE bool IsEmpty() const
	{
		return ItemCode.IsNone();
	}

	// �ش� �����͸� ���
	FORCEINLINE void Clear()
	{
		ItemCode = TEXT("");
	}
};
