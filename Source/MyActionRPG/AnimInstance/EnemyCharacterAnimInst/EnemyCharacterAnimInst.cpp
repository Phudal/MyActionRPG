// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/EnemyCharacterAnimInst/EnemyCharacterAnimInst.h"

#include "Actor/Character/EnemyCharacter/EnemyCharacter.h"

void UEnemyCharacterAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEnemyCharacter* owner = Cast<AEnemyCharacter>(TryGetPawnOwner());

	if (!IsValid(owner))
		return;

	VelocityLength = owner->GetVelocity().Size();
}
