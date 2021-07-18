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
	// ������ ��ų �ڵ�
	FName ProgressSkillCode;

	// ��ų ��Ÿ��
	float SkillCoolTime;

	// ��ų ���� �ð�
	float SkillCastTime;

	// ��ų �޺�
	int32 SkillCombo;

	// ���� ��ų ���� �ε���
	int CurrentSkillRangeIndex;

public:
	FSkillProgressInfo();
	FSkillProgressInfo(
		FName progressSkillCode,
		float skillCoolTime,
		float skillCastTime,
		int32 skillCombo = 0,
		int currentSkillRangeIndex = 0);

	// �޺� ī��Ʈ�� ����
	FORCEINLINE void AddCombo()
	{
		SkillCombo = SkillCombo + 1;
	}

	FORCEINLINE void ResetCombo()
	{
		SkillCombo = 0;
	}

	// ��ų ���� �ε����� �ʱ�ȭ
	FORCEINLINE void ResetSkillRangeIndex()
	{
		CurrentSkillRangeIndex = 0;
	}
};
