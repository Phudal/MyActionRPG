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

	// 플레이어 캐릭터를 나타냄
	class APlayerCharacter* PlayerCharacter;

	// 현재 실행중인 스킬 정보를 나타냄
	FSkillInfo* CurrentSkillInfo;

	// 바로 이전에 실행시킨 스킬 정보를 나타냄
	FSkillInfo* PrevSkillInfo;

	// 실행했었던 스킬 정보를 담아둘 맵
	/// - 콤보와 쿨타임을 계산하기 위해 사용됨
	TMap<FName, FSkillProgressInfo> UsedSkillInfo;

	// 실행시킬 스킬들을 담아둘 큐
	TQueue<FSkillInfo*> SkillQueue;

	// 입력된 스킬 카운트를 나타냄
	int32 SkillCount;

	// 스킬을 요청할 수 있음을 나타냄
	/// - 이 값이 false 라면 스킬 실행을 요청할 수 없음
	bool bIsRequestable;

	
public:	
	// Sets default values for this component's properties
	USkillControllerComponent();

public:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 스킬을 순서대로 처리함
	void SkillProdecure();

	// 사용된 스킬 상태를 갱신함
	void UpdateUsedSkillInfo(FSkillInfo* newSkillInfo);

	// 스킬을 시전함
	void CastSkill(FSkillInfo* skillInfo);

	void MakeSkillRange(
		FSkillInfo* skillInfo,
		FVector tracingStart,
		FVector tracingEnd,
		float radius,
		FName profileName);

public:
	// 스킬 실행을 요청함
	/// - skillCode : 요청시킬 스킬 코드를 전달
	void RequestSkill(FName skillCode);

public:
	FORCEINLINE void SetSkillRequestable(bool bRequestable)
	{
		bIsRequestable = bRequestable;
	}

	// 스킬이 끝났음을 알림
	void SkillFinished();

	// 스킬 범위 인덱스를 다음 인덱스로 변경함
	void NextSkillRangeIndex();

	// 스킬 범위를 생성함
	void MakeSkillRange();
};
