// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemySpawnRegionInfo.generated.h"


// 적의 스폰 지점 정보를 나타냄
USTRUCT(BlueprintType)
struct MYACTIONRPG_API FEnemySpawnRegionInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxEnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> EnemyCode;

public:
	FEnemySpawnRegionInfo();
};
