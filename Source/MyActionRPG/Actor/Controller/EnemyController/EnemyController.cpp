// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/EnemyController/EnemyController.h"

#include "Enum/Team.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AEnemyController::AEnemyController()
{
	// AI Controller 의 자극 감지 컴포넌트를 설정함
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION")));
	/// - UAIPerceptionComponent : AI 의 특정한 자극을 감지하는 컴포넌트를 나타냄
	/// - 이렇게 생성한 자극 감지 컴포넌트를 GetPerceptionComponent() 를 이용하여 다시 얻을 수 있음
	
	// AI 의 팀을 설정함
	SetGenericTeamId(FGenericTeamId(ETeam::Enemy));

	// Sight Sense
	{
		// 시각 자극 객체 생성
		AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_PERCEPTION"));

		// 시야 거리를 설정함
		AISightConfig->SightRadius = 500.0f;

		// 시야 상실 거리를 설정함
		AISightConfig->LoseSightRadius = 650.0f;

		// 한쪽 눈의 시야각을 설정함
		AISightConfig->PeripheralVisionAngleDegrees = 180.0f;

		// 자극이 소멸되기 까지 걸리는 시간을 설정함
		AISightConfig->SetMaxAge(2.0f);

		// 적이 감지되도록 함
		AISightConfig->DetectionByAffiliation.bDetectEnemies = true;

		// 같은 팀이 감지되지 않도록 함
		AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;

		// 중립 팀이 감지되지 않도록 함
		AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;

		// 해당 설정을 사용하는 시각 자극 객체를 적용 시킴
		GetPerceptionComponent()->ConfigureSense(*AISightConfig);

		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnSightUpdated);
	}

	TrackingTargetActor = nullptr;
}

bool AEnemyController::UpdateTrackingPosition()
{
	if (TrackingTargetActor == nullptr)
	{
		// UE_LOG(LogTemp, Log, TEXT("TrackingTargetActor == nullptr"));
		return false;
	}
	
	else
	{
		FVector lineTraceStartLoc = TrackingTargetActor->GetActorLocation();
		FVector lineTraceEndLoc = lineTraceStartLoc + (FVector::DownVector * 1000.0f);

		TArray<AActor*> hitActors;
		FHitResult hitResult;		
		
		if (UKismetSystemLibrary::LineTraceSingleByProfile(
			GetWorld(),
			lineTraceStartLoc,
			lineTraceEndLoc,
			FName(TEXT("SpawnEnemy")),
			true,
			hitActors,
			EDrawDebugTrace::ForDuration,
			hitResult,
			true
			))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPosition"), hitResult.Location);

			// UE_LOG(LogTemp, Log, TEXT("%f, %f, %f"), hitResult.Location.X, hitResult.Location.Y, hitResult.Location.Z);

			UE_LOG(LogTemp,Log, TEXT("%d"), hitActors.Num());
						
			
			UE_LOG(LogTemp, Log, TEXT("%s"), *GetBlackboardComponent()->GetValueAsVector(TEXT("TargetPosition")).ToString());
			
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("LineTraceSingleByProfile - false"));
			return false;
		}
	}
}


void AEnemyController::OnSightUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// 시야에 들어왔다면
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Log, TEXT("시야 검출됨"));
		TrackingTargetActor = Actor;
	}
	// 시야에서 사라졌다면
	else
	{
		UE_LOG(LogTemp, Log, TEXT("시야 검출되지 않음"));
		TrackingTargetActor = nullptr;
	}
}
