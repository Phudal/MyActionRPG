// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API UPlayerCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()

private:
	class APlayerCharacter* Owner;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInAir;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void AnimNotify_SkillFinished();

	UFUNCTION()
	void AnimNotify_SetSkillRequestable();

	UFUNCTION()
	void AnimNotify_BlockSkillRequestable();

	UFUNCTION()
	void AnimNotify_MakeSkillRange();

	UFUNCTION()
	void AnimNotify_MakeNextSkillRange();
	
};
