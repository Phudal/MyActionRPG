// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SkillControllerComponent/SkillControllerComponent.h"

#include "Single/GameInstance/RPGGameInst.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

// Sets default values for this component's properties
USkillControllerComponent::USkillControllerComponent()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILL_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_SkillInfo.DT_SkillInfo'"));

	if (DT_SKILL_INFO.Succeeded())
		DT_SkillInfo = DT_SKILL_INFO.Object;
	
	PrimaryComponentTick.bCanEverTick = true;

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	SkillCount = 0;
	bIsRequestable = true;
	CurrentSkillInfo = PrevSkillInfo = nullptr;
}


// Called when the game starts
void USkillControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void USkillControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SkillProdecure();
}

void USkillControllerComponent::SkillProdecure()
{
	// 현재 실행중인 스킬이 존재한다면 return
	/// - 스킬은 순차적으로 하나씩 진행되도록 함
	if (CurrentSkillInfo != nullptr)
		return;

	// 큐에 요소가 존재하지 않는다면 실행하지 않음
	if (SkillQueue.IsEmpty())
		return;

	// 다음에 실생시킬 스킬 정보를 얻음
	FSkillInfo* skillInfo;
	SkillQueue.Dequeue(skillInfo);

	--SkillCount;

	// 스킬 상태 갱신
	UpdateUsedSkillInfo(skillInfo);

	// 스킬을 실행
	CastSkill(skillInfo);
}

void USkillControllerComponent::UpdateUsedSkillInfo(FSkillInfo* newSkillInfo)
{
	// 전에 사용한 스킬이 현재 사용될 스킬과 같은 스킬이 아니라면, 이전 스킬이 다음에 사용되었을 때
	// 연계 시작 가능한 상태로 설정
	if (PrevSkillInfo != nullptr)
	{
		if (PrevSkillInfo->SkillCode != newSkillInfo->SkillCode)
		{
			UsedSkillInfo[PrevSkillInfo->SkillCode].SkillCombo = -1;
		}
	}

	// 이전에 스킬이 사용된 적이 있다면
	if (UsedSkillInfo.Contains(newSkillInfo->SkillCode))
	{
		// 콤보를 사용하는 스킬이라면
		if (newSkillInfo->GetMaxComboCount() != 0)
		{
			// 콤보 카운트를 증가
			UsedSkillInfo[newSkillInfo->SkillCode].AddCombo();

			// 콤보 카운트가 최대 콤보 카운트를 초과한다면 리셋시킴
			if (UsedSkillInfo[newSkillInfo->SkillCode].SkillCombo == newSkillInfo->GetMaxComboCount())
			{
				UsedSkillInfo[newSkillInfo->SkillCode].ResetCombo();

				// 전에 사용했던 스킬 범위 인덱스를 초기화함
				UsedSkillInfo[PrevSkillInfo->SkillCode].ResetSkillRangeIndex();
			}
		}
	}

	// 스킬을 처음 사용한다면 새로운 데이터를 추가
	else
	{
		FSkillProgressInfo NewSkillProgressInfo = FSkillProgressInfo(
			newSkillInfo->SkillCode,
			0.0f, 0.0f,
			0);

		UsedSkillInfo.Add(newSkillInfo->SkillCode, NewSkillProgressInfo);
	}
}

void USkillControllerComponent::CastSkill(FSkillInfo* skillInfo)
{
	// 새로운 스킬을 현재 사용 스킬로 설정함
	CurrentSkillInfo = skillInfo;

	// 스킬 요청 불가능 상태로 설정함
	bIsRequestable = false;

	// 애니메이션을 재생함
	UAnimMontage* skillAnimMontage = Cast<UAnimMontage>(
		GetManager(FStreamableManager)->LoadSynchronous(CurrentSkillInfo->AnimMontagePath));

	// 이전에 사용한 스킬이 존재한다면
	if (PrevSkillInfo != nullptr)
	{
		// 같은 스킬을 연계 공격으로 사용했다면
		if ((PrevSkillInfo->SkillCode == CurrentSkillInfo->SkillCode) &&
			CurrentSkillInfo->LinkableSkillSectionNames.Num() != 0)
		{
			// 애님 몽타주 섹션 이름을 얻음
			int32 currentComboCount = UsedSkillInfo[CurrentSkillInfo->SkillCode].SkillCombo;
			FName sectionName = CurrentSkillInfo->LinkableSkillSectionNames[currentComboCount];

			// 저장한 섹션의 애니메이션을 재생함
			PlayerCharacter->PlayAnimMontage(skillAnimMontage, 1.0f, sectionName);
			return;
		}
		// 다른 스킬을 사용했다면
		else
		{
			// 이전에 사용한 스킬을 다음에 사용되었을 때 연계 시작 가능한 상태로 설정함
			UsedSkillInfo[PrevSkillInfo->SkillCode].SkillCombo = -1;
		}
	}

	PlayerCharacter->PlayAnimMontage(skillAnimMontage);
}

void USkillControllerComponent::MakeSkillRange(
	FSkillInfo* skillInfo, 
	FVector tracingStart, 
	FVector tracingEnd,
	float radius, 
	FName profileName)
{
	// 감지 무시 대상 액터들을 나타냄
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());

	// 감지 결과를 담은 배열을 나타냄
	TArray<FHitResult> hitResults;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		tracingStart,
		tracingEnd,
		radius,
		profileName,
		true,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		hitResults,
		true);

	for (FHitResult hitresult : hitResults)
	{
		//
	}
}

void USkillControllerComponent::RequestSkill(FName skillCode)
{
}

void USkillControllerComponent::SkillFinished()
{
}

void USkillControllerComponent::NextSkillRangeIndex()
{
}

void USkillControllerComponent::MakeSkillRange()
{
}

