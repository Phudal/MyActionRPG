// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"

#include "Components/ActorComponent.h"

#include "Struct/SkillInfo/SkillInfo.h"
#include "Struct/SkillProgressInfo/SkillProgressInfo.h"

#include "SkillControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONRPG_API USkillControllerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class UDataTable* DT_SkillInfo;

private:
	class ABaseLevelScriptActor* CurrentLevel;

	// �÷��̾� ĳ���͸� ��Ÿ��
	class APlayerCharacter* PlayerCharacter;

	// ���� �������� ��ų ������ ��Ÿ��
	FSkillInfo* CurrentSkillInfo;

	// �ٷ� ������ �����Ų ��ų ������ ��Ÿ��
	FSkillInfo* PrevSkillInfo;

	// �����߾��� ��ų ������ ��Ƶ� ��
	/// - �޺��� ��Ÿ���� ����ϱ� ���� ����
	TMap<FName, FSkillProgressInfo> UsedSkillInfo;

	// �����ų ��ų���� ��Ƶ� ť
	TQueue<FSkillInfo*> SkillQueue;

	// �Էµ� ��ų ī��Ʈ�� ��Ÿ��
	int32 SkillCount;

	// ��ų�� ��û�� �� ������ ��Ÿ��
	/// - �� ���� false ��� ��ų ������ ��û�� �� ����
	bool bIsRequestable;

	
public:	
	// Sets default values for this component's properties
	USkillControllerComponent();

public:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// ��ų�� ������� ó����
	void SkillProdecure();

	// ���� ��ų ���¸� ������
	void UpdateUsedSkillInfo(FSkillInfo* newSkillInfo);

	// ��ų�� ������
	void CastSkill(FSkillInfo* skillInfo);

	void MakeSkillRange(
		FSkillInfo* skillInfo,
		FVector tracingStart,
		FVector tracingEnd,
		float radius,
		FName profileName);

public:
	// ��ų ������ ��û��
	/// - skillCode : ��û��ų ��ų �ڵ带 ����
	void RequestSkill(FName skillCode);

public:
	FORCEINLINE void SetSkillRequestable(bool bRequestable)
	{
		bIsRequestable = bRequestable;
	}

	// ��ų�� �������� �˸�
	void SkillFinished();

	// ��ų ���� �ε����� ���� �ε����� ������
	void NextSkillRangeIndex();

	// ��ų ������ ������
	void MakeSkillRange();
};
