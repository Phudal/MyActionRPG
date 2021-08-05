// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_UpdateTrackingPosition.h"

#include "Actor/Controller/EnemyController/EnemyController.h"

EBTNodeResult::Type UBTTask_UpdateTrackingPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyController* enemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	if (enemyController->UpdateTrackingPosition())
	{
		//UE_LOG(LogTemp, Log, TEXT("BTTask_UpdateTrackingPosition - Succeeded"));
		return EBTNodeResult::Succeeded;
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("BTTask_UpdateTrackingPosition - Faild"));
		return EBTNodeResult::Failed;
	}
}
