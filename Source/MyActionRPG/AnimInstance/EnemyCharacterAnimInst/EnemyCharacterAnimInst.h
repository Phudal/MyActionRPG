// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacterAnimInst.generated.h"


UCLASS()
class MYACTIONRPG_API UEnemyCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
