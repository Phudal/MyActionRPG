// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/PlayerBehavior.h"

#include "PlayerBehaviorData.generated.h"


USTRUCT()
struct MYACTIONRPG_API FPlayerBehaviorData
{
	GENERATED_USTRUCT_BODY()

public:
	// �ൿ Ÿ���� ��Ÿ��
	EPlayerBehavior::Type Behavior;

	// ������ �ڵ�, NPC �ڵ�, ���� �ڵ� ���� ��Ÿ��
	FName Code;

	// ������ ��Ÿ��
	int32 Count;

	// Ư���� ���ڿ��� ���޵�
	FString StringData;

public:
	FPlayerBehaviorData(EPlayerBehavior::Type behavior = EPlayerBehavior::BH_None);
	FPlayerBehaviorData(EPlayerBehavior::Type behavior, FString stringData);
	FPlayerBehaviorData(EPlayerBehavior::Type behavior, FName code, int32 count);

public:
	// ������ ���� ����
	FORCEINLINE int32 GetItemCount() const
	{
		return Count;
	}	
};
