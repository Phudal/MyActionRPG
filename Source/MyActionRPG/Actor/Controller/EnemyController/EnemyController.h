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
	// 자극 감지 객체에서 사용될 시각 자극 객체를 나타냄
	class UAISenseConfig_Sight* AISightConfig;

	// 추적 목표 액터를 나타냄
	AActor* TrackingTargetActor;

public:
	AEnemyController();

	// 추적 위치를 갱신함
	/// - TrackingTargetActor 가 nullptr 인 경우 false를 반환
	bool UpdateTrackingPosition();

	bool TestingBool();
	
private:
	void OnSightUpdated(AActor* Actor, FAIStimulus Stimulus);
	/// - Actor : 상태가 갱신된 액터가 전달됨
	/// - Stimulus : 상태 갱신 결과에 대한 세부적인 정보들을 나타냄
};
