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
	// 행동 타입을 나타냄
	EPlayerBehavior::Type Behavior;

	// 아이템 코드, NPC 코드, 몬스터 코드 등을 나타냄
	FName Code;

	// 수량을 나타냄
	int32 Count;

	// 특정한 문자열이 전달됨
	FString StringData;

public:
	FPlayerBehaviorData(EPlayerBehavior::Type behavior = EPlayerBehavior::BH_None);
	FPlayerBehaviorData(EPlayerBehavior::Type behavior, FString stringData);
	FPlayerBehaviorData(EPlayerBehavior::Type behavior, FName code, int32 count);

public:
	// 아이템 수를 얻음
	FORCEINLINE int32 GetItemCount() const
	{
		return Count;
	}	
};
