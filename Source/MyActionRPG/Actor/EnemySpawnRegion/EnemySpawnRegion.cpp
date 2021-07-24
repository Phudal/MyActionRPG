// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemySpawnRegion/EnemySpawnRegion.h"

#include "Component/EnemySpawnerComponent/EnemySpawnerComponent.h"
#include "Components/BillboardComponent.h"

// Sets default values
AEnemySpawnRegion::AEnemySpawnRegion()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> T_ENEMY_SPAWN_REGION_ICON(
		TEXT("Texure2D'/Game/Resources/Image/Props/Icon/T_EnemySpawnRegionIcon.T_EnemySpawnRegionIcon'"));

	if (T_ENEMY_SPAWN_REGION_ICON.Succeeded())
		T_EnemySpawnRegionIcon = T_ENEMY_SPAWN_REGION_ICON.Object;
	
	PrimaryActorTick.bCanEverTick = false;

	RegionCode = FName(TEXT("1000"));

	EnemySpawner = CreateDefaultSubobject<UEnemySpawnerComponent>(TEXT("ENEMY_SPAWNER_COMPONENT"));
	SetRootComponent(EnemySpawner);

	BillboardRegionIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("BILLBOARD_COMPONENT"));
	BillboardRegionIcon->SetupAttachment(GetRootComponent());
	BillboardRegionIcon->SetSprite(T_EnemySpawnRegionIcon);
	BillboardRegionIcon->SetRelativeLocation(FVector::UpVector * 200.0f);

}


