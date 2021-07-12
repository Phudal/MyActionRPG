// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PlayerCharacterAnimInst/PlayerCharacterAnimInst.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Component/CharacterMovementHelper/CharacterMovementHelperComponent.h"

// TODO
// SkillController Ãß°¡ 

void UPlayerCharacterAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Owner = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner))
		return;

	VelocityLength = Owner->GetVelocity().Size();

	bIsInAir = Owner->GetCharacterMovementHelper()->IsInAir();
}

void UPlayerCharacterAnimInst::AnimNotify_SkillFinished()
{
}

void UPlayerCharacterAnimInst::AnimNotify_SetSkillRequestable()
{
}

void UPlayerCharacterAnimInst::AnimNotify_BlockSkillRequestable()
{
}

void UPlayerCharacterAnimInst::AnimNotify_MakeSkillRange()
{
}

void UPlayerCharacterAnimInst::AnimNotify_MakeNextSkillRange()
{
}
