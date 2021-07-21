// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/PoolableParticle/PoolableParticle.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APoolableParticle::APoolableParticle()
{
	INITIALIZE_OBJECT_POOLABLE(NOT_USE_INSTANCE_ID);
	PrimaryActorTick.bCanEverTick = true;

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE_SYSTEM"));
	SetRootComponent(ParticleSystem);
}

// Called when the game starts or when spawned
void APoolableParticle::BeginPlay()
{
	Super::BeginPlay();

	ParticleSystem->OnSystemFinished.AddDynamic(this, &APoolableParticle::OnParticleSystemFinished);
}

// Called every frame
void APoolableParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableParticle::OnRecycleStart()
{
}

void APoolableParticle::OnParticleSystemFinished(UParticleSystemComponent* pSystem)
{
	SetCanRecyclable(true);
}

