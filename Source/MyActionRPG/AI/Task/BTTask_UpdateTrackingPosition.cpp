// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_UpdateTrackingPosition.h"

#include "Actor/Controller/EnemyController/EnemyController.h"

EBTNodeResult::Type UBTTask_UpdateTrackingPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyController* enemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	if (enemyController->UpdateTrackingPosition())
		return EBTNodeResult::Succeeded;

	else if (enemyController->TestingBool())
		return EBTNodeResult::Failed;

	return EBTNodeResult::Failed;
}
