// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EnemySpawnRegion.generated.h"

UCLASS()
class MYACTIONRPG_API AEnemySpawnRegion : public AActor
{
	GENERATED_BODY()

private:
	class UTexture2D* T_EnemySpawnRegionIcon;
	
private:
	// 적 스폰 지점 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Region Code")
	FName RegionCode;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UEnemySpawnerComponent* EnemySpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* BillboardRegionIcon;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnRegion();

	FORCEINLINE FName GetRegionCode() const
	{
		return RegionCode;
	}
};
