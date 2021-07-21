// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Level/BaseLevelScriptActor.h"

#include "Actor/PoolableParticle/PoolableParticle.h"
#include "Particles/ParticleSystemComponent.h"


ABaseLevelScriptActor::ABaseLevelScriptActor()
{
	PoolableParticleClass = APoolableParticle::StaticClass();
}

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	ParticlePool = NewObject<UObjectPool>();
}

APoolableParticle* ABaseLevelScriptActor::CreatePoolableParticleActor(UParticleSystem* particleTemplate,
	FVector location, FRotator rotation)
{
	APoolableParticle* poolableParticle = ParticlePool->GetRecycledObject<APoolableParticle>();

	poolableParticle = (poolableParticle != nullptr) ?
		poolableParticle :
		GetWorld()->SpawnActor<APoolableParticle>(
			PoolableParticleClass);

	poolableParticle->SetActorLocationAndRotation(location, rotation);

	poolableParticle->GetParticleSystem()->SetTemplate(particleTemplate);
	poolableParticle->GetParticleSystem()->Activate(true);

	return poolableParticle;
}

