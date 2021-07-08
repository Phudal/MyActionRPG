// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/CharacterClassType.h"
#include "CharacterClassInfo.generated.h"

USTRUCT(BlueprintType)
struct MYACTIONRPG_API FCharacterClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 캐릭터 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "클래스")
	ECharacterClassType ClassType;

	// 기본으로 장착되는 장비 아이템 코드들을 나타냄
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기타")
	TArray<FName> DefaultEquipItemCodes;
};
