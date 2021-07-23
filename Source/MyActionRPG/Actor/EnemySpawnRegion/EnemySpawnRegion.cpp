// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemySpawnRegion/EnemySpawnRegion.h"

// Sets default values
AEnemySpawnRegion::AEnemySpawnRegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawnRegion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnRegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

