// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerBehaviorBroadcast/PlayerBehaviorBroadcastComponent.h"

// Sets default values for this component's properties
UPlayerBehaviorBroadcastComponent::UPlayerBehaviorBroadcastComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerBehaviorBroadcastComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerBehaviorEvents.Add(EPlayerBehavior::BH_None, FPlayerBehaviorEvent());
	PlayerBehaviorEvents.Add(EPlayerBehavior::BH_GetItem, FPlayerBehaviorEvent());
	PlayerBehaviorEvents.Add(EPlayerBehavior::BH_StartQuest, FPlayerBehaviorEvent());
	PlayerBehaviorEvents.Add(EPlayerBehavior::BH_FinishQuest, FPlayerBehaviorEvent());	
}


// Called every frame
void UPlayerBehaviorBroadcastComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	BehaviorProcedure();
}

void UPlayerBehaviorBroadcastComponent::BehaviorProcedure()
{
	// 발생한 행동이 존재하지 않는다면 실행하지 않음
	if (PlayerBehaviors.IsEmpty())
		return;

	// 추가된 행동을 얻음
	FPlayerBehaviorData newBehavior;
	PlayerBehaviors.Dequeue(newBehavior);

	// 행동 타입에 따라 이벤트를 실행
	PlayerBehaviorEvents[newBehavior.Behavior].Broadcast(newBehavior);
}

void UPlayerBehaviorBroadcastComponent::AddBehavior(FPlayerBehaviorData newBehaviorData)
{
	PlayerBehaviors.Enqueue(newBehaviorData);
}

