// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Animation/AnimInstance.h"
#include "EnemyData.generated.h"


USTRUCT(BlueprintType)
struct MYACTIONRPG_API FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 적 코드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "기본")
	FName EnemyCode;

	// 적 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "기본")
	FText EnemyName;

	// 적 Capsule 크기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "기본")
	float CapsuleHalfHeight;

	// 적 Capsule 반지름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "기본")
	float CapsuleRadius;
	
	// 적 SkeletalMesh 경로
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "기본")
	FSoftObjectPath SkeletalMeshPath;

	// 적 애님 블루프린트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "기본")
	TSubclassOf<UAnimInstance> AnimClass;

	// 최대 이동 속력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "이동")
	float MaxMoveSpeed;

	// 사용되는 BehaviorTree 에셋 경로
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FSoftObjectPath UseBehaviorTreeAssetPath;

public:
	FEnemyData();
};
