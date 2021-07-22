// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MoveToPlayer.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Actor/Controller/EnemyController/EnemyController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyController* enemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());	
	APlayerCharacter* playerCharacter = GetManager(UPlayerManager)->GetPlayerCharacter();

	if (!IsValid(playerCharacter))
		return EBTNodeResult::Failed;

	//enemyController->GetBlackboardComponent()->SetValueAsVector(
	//	FName(TEXT("TargetPosition")),
	//	playerCharacter->GetActorLocation());

	return EBTNodeResult::Succeeded;
}
