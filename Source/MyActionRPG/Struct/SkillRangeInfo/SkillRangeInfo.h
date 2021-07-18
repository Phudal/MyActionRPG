// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/SkillRangeDirection.h"
#include "SkillRangeInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYACTIONRPG_API FSkillRangeInfo	
{
	GENERATED_USTRUCT_BODY()

public:
	// Sphere Trace ��� ���θ� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseSphereTrace;

	// ĳ���Ͱ� ������ �Ǵ� Ʈ���̽� ���� ��ġ ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TraceStartOffset;

	// Ʈ���̽� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillRangeDirection TraceDirection;

	// Sphere Trace �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceDistance;

	// Sphere Trace �� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceRadius;

	// ��ų ����� ������ ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DamageCalcFormula;

	// ���� ���� ���� �� ���� ���� �����̸� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CreateDelay;

public:
	FSkillRangeInfo();

	// basedActor �� �������� �ϴ� TraceDirection ������ ��Ÿ��
	FVector GetTraceDirection(AActor* basedActor);

	// �� ������ Ÿ�� Ƚ����, ������� ��ȯ
	TTuple<int32, float> GetSkillCalcFormulaResult();
};
