// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PlayerCharacterAnimInst/PlayerCharacterAnimInst.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Component/CharacterMovementHelper/CharacterMovementHelperComponent.h"
#include "Component/SkillControllerComponent/SkillControllerComponent.h"

// TODO
// SkillController �߰� 

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
	if (!IsValid(Owner))
		return;
	Owner->GetSkillController()->SkillFinished();
}

void UPlayerCharacterAnimInst::AnimNotify_SetSkillRequestable()
{
	if (!IsValid(Owner))
		return;
	Owner->GetSkillController()->SetSkillRequestable(true);
}

void UPlayerCharacterAnimInst::AnimNotify_BlockSkillRequestable()
{
	if (!IsValid(Owner))
		return;
	Owner->GetSkillController()->SetSkillRequestable(false);
}

void UPlayerCharacterAnimInst::AnimNotify_MakeSkillRange()
{
	if (!IsValid(Owner))
		return;
	Owner->GetSkillController()->MakeSkillRange();
}

void UPlayerCharacterAnimInst::AnimNotify_MakeNextSkillRange()
{
	if (!IsValid(Owner))
		return;
	Owner->GetSkillController()->NextSkillRangeIndex();
	Owner->GetSkillController()->MakeSkillRange();
}
