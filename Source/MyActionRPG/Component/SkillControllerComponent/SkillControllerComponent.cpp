// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SkillControllerComponent/SkillControllerComponent.h"

#include "Single/GameInstance/RPGGameInst.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Actor/Level/BaseLevelScriptActor.h"


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
	
	CurrentLevel = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
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
	UE_LOG(LogTemp, Log, TEXT("CastSkill Begin"));
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

	UE_LOG(LogTemp, Log, TEXT("CastSkill End"));
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
		CurrentLevel->CreatePoolableParticleActor(
			Cast<UParticleSystem>(GetManager(FStreamableManager)->LoadSynchronous(skillInfo->HitParticle)),
			hitresult.ImpactPoint);
	}
}

void USkillControllerComponent::RequestSkill(FName skillCode)
{
	UE_LOG(LogTemp, Log, TEXT("RequestSkill Start"))
	// ��ų�� ��û�� �� ���� ��� �������� ����
	if (!bIsRequestable)
	{
		UE_LOG(LogTemp, Log, TEXT("bIsRequestable is false"));
		return;
	}	
	
	// ��ų�� 3�� �̻� ��ϵƴٸ� �������� ����
	if (SkillCount >= 3)
		return;

	FString contextString;
	FSkillInfo* requestSkillInfo = DT_SkillInfo->FindRow<FSkillInfo>(skillCode, contextString);

	// ��û�� ��ų�� ã�� ������ ��� ��û ���
	if (requestSkillInfo == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("requestSkillInfo is nullptr"));
		return;
	}
	// �����ų ��ų�� ��� ť�� �߰�
	SkillQueue.Enqueue(requestSkillInfo);
	SkillCount++;

	UE_LOG(LogTemp, Log, TEXT("RequestSkill End"));
}

void USkillControllerComponent::SkillFinished()
{
	// ���� ��ų�� ���� ��ų ������ ����
	PrevSkillInfo = CurrentSkillInfo;
	CurrentSkillInfo = nullptr;

	// ��ų ��û ���� ���·� ����
	bIsRequestable = true;

	// ����� ��ų�� �������� �ʴ´ٸ�
	if (SkillCount == 0)
	{
		// ������ ����� ��ų�� ������ ���Ǿ��� �� ���� ���� ������ ���·� ������
		UsedSkillInfo[PrevSkillInfo->SkillCode].SkillCombo = -1;

		// ����ߴ� ��ų ���� �ε����� �ʱ�ȭ
		UsedSkillInfo[PrevSkillInfo->SkillCode].ResetSkillRangeIndex();
	}
}

void USkillControllerComponent::NextSkillRangeIndex()
{
	// ���� �������� ��ų�� �������� �ʴ´ٸ� �������� ����
	if (CurrentSkillInfo == nullptr)
		return;

	// ��ų ���� �ε��� ����
	++UsedSkillInfo[CurrentSkillInfo->SkillCode].CurrentSkillRangeIndex;

	// ���� �ε����� �迭 ������ �ʰ��Ѵٸ� ������ ��Ҹ� ����ϵ��� ��
	if (UsedSkillInfo[CurrentSkillInfo->SkillCode].CurrentSkillRangeIndex ==
		CurrentSkillInfo->SkillRangeInfos.Num())
		--UsedSkillInfo[CurrentSkillInfo->SkillCode].CurrentSkillRangeIndex;
}

void USkillControllerComponent::MakeSkillRange()
{
	int32 currentSkillRangeIndex = UsedSkillInfo[CurrentSkillInfo->SkillCode].CurrentSkillRangeIndex;

	// ��ų ���� ������ ����
	FSkillRangeInfo skillRangeInfo = CurrentSkillInfo->SkillRangeInfos[currentSkillRangeIndex];
	TTuple<int32, float> calcFormulaRes = skillRangeInfo.GetSkillCalcFormulaResult();
	int32 rangeCount = calcFormulaRes.Get<0>();
	float value = calcFormulaRes.Get<1>();

	// LOG(TEXT("form = %s"), *skillRangeInfo.DamageCalcFormula);
	UE_LOG(LogTemp, Log, TEXT("form = %s"), *skillRangeInfo.DamageCalcFormula);

	// sphere Tracing�� ������� �ʴ´ٸ� �������� ����
	if (!skillRangeInfo.bUseSphereTrace)
		return;

	// Ʈ���̽� �������� ����
	FVector tracingOffset =
		(GetOwner()->GetActorForwardVector() * skillRangeInfo.TraceStartOffset.X) +
		(GetOwner()->GetActorRightVector() * skillRangeInfo.TraceStartOffset.Y) +
		(GetOwner()->GetActorUpVector() * skillRangeInfo.TraceStartOffset.Z);

	// Ʈ���̽� ���� ��ġ�� ��Ÿ��
	FVector tracingStart = GetOwner()->GetActorLocation() + tracingOffset;

	// Ʈ���̽� ����
	FVector tracingDirection = skillRangeInfo.GetTraceDirection(GetOwner());

	// Ʈ���̽� �� ��ġ
	FVector tracingEnd = tracingStart + (tracingDirection * skillRangeInfo.TraceDistance);

	// ����ϴ� ��ų ������ ��Ÿ��
	FSkillInfo* skillInfo = CurrentSkillInfo;

	for (int32 i = 0; i < rangeCount; i++)
	{
		if (FMath::IsNearlyZero(skillRangeInfo.CreateDelay) || (i == 0))
		{
			MakeSkillRange(skillInfo, tracingStart, tracingEnd, skillRangeInfo.TraceRadius, FName(TEXT("PlayerSkill")));			
		}
		else
		{
			FTimerHandle timerHandle;
			FTimerDelegate timerDelegate;

			timerDelegate.BindLambda([skillInfo, tracingStart, tracingEnd, skillRangeInfo, this]()
				{
					MakeSkillRange(skillInfo, tracingStart, tracingEnd, skillRangeInfo.TraceRadius, FName(TEXT("PlayerSkill")));
				});

			// Ÿ�̸� ����
			GetWorld()->GetTimerManager().
				SetTimer(timerHandle, timerDelegate, skillRangeInfo.CreateDelay * i, false);
		}
	}                      
}

