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
	// ���� ������ X �� �������� �� �� ��ġ�ϵ��� �� �������� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Region Settings", meta = (AllowPrivateAccess = "true"))
	int32 SpawnPointXCount;

	// ���� ������ X �� �������� �� �� ��ġ�ϵ��� �� �������� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Region Settings", meta = (AllowPrivateAccess = "true"))
	int32 SpawnPointYCount;

	// ���� Ʈ���̽� ���� ���̸� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Region Settings", meta = (AllowPrivateAccess = "true"))
	float LineTraceStartHeight;

	// �� ���� ���� ������ ��Ÿ��
	struct FEnemySpawnRegionInfo* SpawnRegionInfo;

	// ���� �������� ��Ÿ��
	TArray<TArray<FVector>> SpawnPoints;

	// ���� ������ �� ��ü��
	int32 CurrentEnemyCount;

public:
	UEnemySpawnerComponent();

	virtual void BeginPlay() override;

private:
	// ���� �������� �ʱ�ȭ��
	void InitializeSpawnPoints();

	void RandomSpawn();

	void SpawnEnemy(FName enemyCode);

	// ������ ���� ��ġ�� ����
	FVector GetRandomSpawnablePoint() const;
};
