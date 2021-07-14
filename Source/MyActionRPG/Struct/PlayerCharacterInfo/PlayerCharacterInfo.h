// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/CharacterClassType.h"
#include "Enum/PartsType.h"

#include "Engine/UserDefinedStruct.h"
#include "PlayerCharacterInfo.generated.h"

/// 있어야 할 것 목록
/// 
/// 캐릭터 클래스 타입
/// 캐릭터 레벨
/// 인벤토리 슬롯 개수
/// 소지중인 아이템 정보
/// 기본 장착 아이템 정보
/// 장착 아이템 정보
/// 소지금
///
/// 진행중인 퀘스트 목록
/// 완료한 퀘스트 목록


USTRUCT()
struct MYACTIONRPG_API FPlayerCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public:
	// 캐릭터 클래스 타입
	UPROPERTY()
	ECharacterClassType CharacterClass;

	// 캐릭터 레벨
	UPROPERTY()
	int32 CharacterLevel;

	
	FPlayerCharacterInfo();

	// 기본 장비 아이템들 초기화
	void InitializeDefaultEquipmentItems(
		TArray<FName>& defaultEquipmentItemCodes, const class UDataTable* dt_EquipmentItemInfo);

	// TODO
	// 장비 아이템 정보를 얻음
};
