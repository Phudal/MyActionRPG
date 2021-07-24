// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EnemySpawnerComponent.generated.h"



UCLASS()
class MYACTIONRPG_API UEnemySpawnerComponent : public UBoxComponent
{
	GENERATED_BODY()

private:
	class UDataTable* DT_EnemySpawnRegionInfo;

private:
	// 스폰 지점이 X 축 방향으로 몇 개 위치하도록 할 것인지를 지정함
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Region Settings", meta = (AllowPrivateAccess = "true"))
	int32 SpawnPointXCount;

	// 스폰 지점이 X 축 방향으로 몇 개 위치하도록 할 것인지를 지정함
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Region Settings", meta = (AllowPrivateAccess = "true"))
	int32 SpawnPointYCount;

	// 라인 트레이스 시작 높이를 지정함
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Region Settings", meta = (AllowPrivateAccess = "true"))
	float LineTraceStartHeight;

	// 적 스폰 지역 정보를 나타냄
	struct FEnemySpawnRegionInfo* SpawnRegionInfo;

	// 스폰 지역들을 나타냄
	TArray<TArray<FVector>> SpawnPoints;

	// 현재 생성된 적 개체수
	int32 CurrentEnemyCount;

public:
	UEnemySpawnerComponent();

	virtual void BeginPlay() override;

private:
	// 스폰 지점들을 초기화함
	void InitializeSpawnPoints();

	void RandomSpawn();

	void SpawnEnemy(FName enemyCode);

	// 랜덤한 스폰 위치를 얻음
	FVector GetRandomSpawnablePoint() const;
};
