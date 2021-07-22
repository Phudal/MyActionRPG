// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/EnemyController/EnemyController.h"

AEnemyController::AEnemyController()
{
}

bool AEnemyController::UpdateTrackingPosition()
{
	if (TrackingTargetActor == nullptr)
		return false;

	else
	{
		FVector lineTraceStartLoc = TrackingTargetActor->GetActorLocation();
		FVector lineTraceEndLoc = lineTraceStartLoc + (FVector::DownVector * 1000.0f);

		TArray<AActor*> hitActors;
		FHitResult hitResult;

		// if ()
		return true;
	}
}

bool AEnemyController::TestingBool()
{
	return true;
}

void AEnemyController::OnSightUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}
