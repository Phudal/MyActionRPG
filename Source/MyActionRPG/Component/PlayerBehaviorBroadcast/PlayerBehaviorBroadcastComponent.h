// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Components/ActorComponent.h"

#include "Struct/PlayerBehaviorData/PlayerBehaviorData.h"

#include "PlayerBehaviorBroadcastComponent.generated.h"


DECLARE_EVENT_OneParam(UPlayerBehaviorBroadcastComponent, FPlayerBehaviorEvent, FPlayerBehaviorData&)
// 이벤트
/// 해당 클래스 내에서만 호출할 수 있는 대리자
/// 기본적으로 MULTICAST
/// 형식 선언 방식 DECLARE_EVENT(이벤트 사용 클래스 명, 이벤트 형식, 매개변수 타입들..)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONRPG_API UPlayerBehaviorBroadcastComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// 특정한 행동을 했을 때 호출되는 대리자들
	TMap<EPlayerBehavior::Type, FPlayerBehaviorEvent> PlayerBehaviorEvents;

	// 행동 데이터가 저장됨
	TQueue<FPlayerBehaviorData> PlayerBehaviors;
	
	
public:	
	UPlayerBehaviorBroadcastComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 발생한 행동을 처리함
	void BehaviorProcedure();

public:
	// 행동을 추가함
	void AddBehavior(FPlayerBehaviorData newBehaviorData);
};
