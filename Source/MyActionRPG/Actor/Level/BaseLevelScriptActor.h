// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"

#include "Util/ObjectPool/ObjectPool.h"

#include "BaseLevelScriptActor.generated.h"


UCLASS()
class MYACTIONRPG_API ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	TSubclassOf<class APoolableParticle> PoolableParticleClass;

private:
	UPROPERTY()
	UObjectPool* ParticlePool;

public:
	ABaseLevelScriptActor();

protected:
	virtual void BeginPlay() override;

public:
	APoolableParticle* CreatePoolableParticleActor(
		class UParticleSystem* particleTemplate,
		FVector location = FVector::ZeroVector,
		FRotator rotation = FRotator::ZeroRotator);

	FORCEINLINE UObjectPool* GetParticlePool() const
	{
		return ParticlePool;
	}
};
