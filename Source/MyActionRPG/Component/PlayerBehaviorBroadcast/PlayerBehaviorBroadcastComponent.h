// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Components/ActorComponent.h"

#include "Struct/PlayerBehaviorData/PlayerBehaviorData.h"

#include "PlayerBehaviorBroadcastComponent.generated.h"


DECLARE_EVENT_OneParam(UPlayerBehaviorBroadcastComponent, FPlayerBehaviorEvent, FPlayerBehaviorData&)
// �̺�Ʈ
/// �ش� Ŭ���� �������� ȣ���� �� �ִ� �븮��
/// �⺻������ MULTICAST
/// ���� ���� ��� DECLARE_EVENT(�̺�Ʈ ��� Ŭ���� ��, �̺�Ʈ ����, �Ű����� Ÿ�Ե�..)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONRPG_API UPlayerBehaviorBroadcastComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Ư���� �ൿ�� ���� �� ȣ��Ǵ� �븮�ڵ�
	TMap<EPlayerBehavior::Type, FPlayerBehaviorEvent> PlayerBehaviorEvents;

	// �ൿ �����Ͱ� �����
	TQueue<FPlayerBehaviorData> PlayerBehaviors;
	
	
public:	
	UPlayerBehaviorBroadcastComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// �߻��� �ൿ�� ó����
	void BehaviorProcedure();

public:
	// �ൿ�� �߰���
	void AddBehavior(FPlayerBehaviorData newBehaviorData);
};
