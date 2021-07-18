// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillProgressInfo.generated.h"


USTRUCT(BlueprintType)
struct MYACTIONRPG_API FSkillProgressInfo :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 실행한 스킬 코드
	FName ProgressSkillCode;

	// 스킬 쿨타임
	float SkillCoolTime;

	// 스킬 시전 시간
	float SkillCastTime;

	// 스킬 콤보
	int32 SkillCombo;

	// 현재 스킬 범위 인덱스
	int CurrentSkillRangeIndex;

public:
	FSkillProgressInfo();
	FSkillProgressInfo(
		FName progressSkillCode,
		float skillCoolTime,
		float skillCastTime,
		int32 skillCombo = 0,
		int currentSkillRangeIndex = 0);

	// 콤보 카운트를 중지
	FORCEINLINE void AddCombo()
	{
		SkillCombo = SkillCombo + 1;
	}

	FORCEINLINE void ResetCombo()
	{
		SkillCombo = 0;
	}

	// 스킬 범위 인덱스를 초기화
	FORCEINLINE void ResetSkillRangeIndex()
	{
		CurrentSkillRangeIndex = 0;
	}
};
