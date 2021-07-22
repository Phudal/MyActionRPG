// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:
	// �ڱ� ���� ��ü���� ���� �ð� �ڱ� ��ü�� ��Ÿ��
	class UAISenseConfig_Sight* AISightConfig;

	// ���� ��ǥ ���͸� ��Ÿ��
	AActor* TrackingTargetActor;

public:
	AEnemyController();

	// ���� ��ġ�� ������
	/// - TrackingTargetActor �� nullptr �� ��� false�� ��ȯ
	bool UpdateTrackingPosition();

	bool TestingBool();
	
private:
	void OnSightUpdated(AActor* Actor, FAIStimulus Stimulus);
	/// - Actor : ���°� ���ŵ� ���Ͱ� ���޵�
	/// - Stimulus : ���� ���� ����� ���� �������� �������� ��Ÿ��
};
