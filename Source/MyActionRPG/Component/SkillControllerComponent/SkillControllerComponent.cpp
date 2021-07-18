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
	// ���� �������� ��ų�� �����Ѵٸ� return
	/// - ��ų�� ���������� �ϳ��� ����ǵ��� ��
	if (CurrentSkillInfo != nullptr)
		return;

	// ť�� ��Ұ� �������� �ʴ´ٸ� �������� ����
	if (SkillQueue.IsEmpty())
		return;

	// ������ �ǻ���ų ��ų ������ ����
	FSkillInfo* skillInfo;
	SkillQueue.Dequeue(skillInfo);

	--SkillCount;

	// ��ų ���� ����
	UpdateUsedSkillInfo(skillInfo);

	// ��ų�� ����
	CastSkill(skillInfo);
}

void USkillControllerComponent::UpdateUsedSkillInfo(FSkillInfo* newSkillInfo)
{
	// ���� ����� ��ų�� ���� ���� ��ų�� ���� ��ų�� �ƴ϶��, ���� ��ų�� ������ ���Ǿ��� ��
	// ���� ���� ������ ���·� ����
	if (PrevSkillInfo != nullptr)
	{
		if (PrevSkillInfo->SkillCode != newSkillInfo->SkillCode)
		{
			UsedSkillInfo[PrevSkillInfo->SkillCode].SkillCombo = -1;
		}
	}

	// ������ ��ų�� ���� ���� �ִٸ�
	if (UsedSkillInfo.Contains(newSkillInfo->SkillCode))
	{
		// �޺��� ����ϴ� ��ų�̶��
		if (newSkillInfo->GetMaxComboCount() != 0)
		{
			// �޺� ī��Ʈ�� ����
			UsedSkillInfo[newSkillInfo->SkillCode].AddCombo();

			// �޺� ī��Ʈ�� �ִ� �޺� ī��Ʈ�� �ʰ��Ѵٸ� ���½�Ŵ
			if (UsedSkillInfo[newSkillInfo->SkillCode].SkillCombo == newSkillInfo->GetMaxComboCount())
			{
				UsedSkillInfo[newSkillInfo->SkillCode].ResetCombo();

				// ���� ����ߴ� ��ų ���� �ε����� �ʱ�ȭ��
				UsedSkillInfo[PrevSkillInfo->SkillCode].ResetSkillRangeIndex();
			}
		}
	}

	// ��ų�� ó�� ����Ѵٸ� ���ο� �����͸� �߰�
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
	// ���ο� ��ų�� ���� ��� ��ų�� ������
	CurrentSkillInfo = skillInfo;

	// ��ų ��û �Ұ��� ���·� ������
	bIsRequestable = false;

	// �ִϸ��̼��� �����
	UAnimMontage* skillAnimMontage = Cast<UAnimMontage>(
		GetManager(FStreamableManager)->LoadSynchronous(CurrentSkillInfo->AnimMontagePath));

	// ������ ����� ��ų�� �����Ѵٸ�
	if (PrevSkillInfo != nullptr)
	{
		// ���� ��ų�� ���� �������� ����ߴٸ�
		if ((PrevSkillInfo->SkillCode == CurrentSkillInfo->SkillCode) &&
			CurrentSkillInfo->LinkableSkillSectionNames.Num() != 0)
		{
			// �ִ� ��Ÿ�� ���� �̸��� ����
			int32 currentComboCount = UsedSkillInfo[CurrentSkillInfo->SkillCode].SkillCombo;
			FName sectionName = CurrentSkillInfo->LinkableSkillSectionNames[currentComboCount];

			// ������ ������ �ִϸ��̼��� �����
			PlayerCharacter->PlayAnimMontage(skillAnimMontage, 1.0f, sectionName);
			return;
		}
		// �ٸ� ��ų�� ����ߴٸ�
		else
		{
			// ������ ����� ��ų�� ������ ���Ǿ��� �� ���� ���� ������ ���·� ������
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
	// ���� ���� ��� ���͵��� ��Ÿ��
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());

	// ���� ����� ���� �迭�� ��Ÿ��
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

