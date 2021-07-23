// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/EnemyCharacter/EnemyCharacter.h"

#include "Single/GameInstance/RPGGameInst.h"

#include "Enum/Team.h"

#include "Actor/Controller/EnemyController/EnemyController.h"

#include "BehaviorTree/BehaviorTree.h"

AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY_DATA(
		TEXT("DataTable'/Game/Resources/DataTables/DT_EnemyData.DT_EnemyData'"));

	if (DT_ENEMY_DATA.Succeeded())
		DT_EnemyData = DT_ENEMY_DATA.Object;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MINO(
		TEXT("SkeletalMesh'/Game/Resources/Enemies/Mino/Mesh/SK_Mino.SK_Mino'"));

	if (SK_MINO.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_MINO.Object);

	// TODO Widget �߰�

	// ����ϴ� AI Controller ����
	AIControllerClass = AEnemyController::StaticClass();

	// ��Ʈ�ѷ� ���� ����� ����
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	BehaviorTree = nullptr;

	// ���� ����
	SetGenericTeamId(ETeam::Enemy);

	
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// �׽�Ʈ�� �ڵ�
	InitializeEnemyCharacter(TEXT("1000"));
}

void AEnemyCharacter::InitializeEnemyCharacter(FName enemyCode)
{
	UE_LOG(LogTemp, Log, TEXT("InitializeEnemyCharacter"));
	EnemyCode = enemyCode;

	// �� �ڵ带 �̿��Ͽ� �� ������ ����
	FString contextString;
	EnemyData = DT_EnemyData->FindRow<FEnemyData>(EnemyCode, contextString);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCharacter"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	/// - SetCollidionProfileName(InCollisionProfileName) : �ݸ��� ��������(Collision Preset)�� ����


	// �� ������ ���������� ���� ���ߴٸ�
	if (EnemyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter.cpp :: %d LINE :: EnemyData is null (EnemyCode Is %s"),
			__LINE__, *EnemyCode.ToString());
		return;
	}

	// TODO
	// ĳ���� ���� �ʱ�ȭ

	// �ִ� �̵� �ӷ� ����
	GetCharacterMovement()->MaxWalkSpeed = EnemyData->MaxMoveSpeed;

	// �� ĸ�� ũ�� ����
	GetCapsuleComponent()->SetCapsuleHalfHeight(EnemyData->CapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleRadius(EnemyData->CapsuleRadius);

	// ���̷�Ż �޽� ����
	USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyData->SkeletalMeshPath));
	/// - LoadSynchronous(target) : target �� �ش��ϴ� �ּ��� ���� ������� �ε��Ͽ� UObject* �������� ��ȯ�մϴ�.
	GetMesh()->SetSkeletalMesh(skeletalMesh);

	// ���̷�Ż �޽� ��ġ / ȸ�� ����
	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// Behavior Tree ����
	BehaviorTree = Cast<UBehaviorTree>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyData->UseBehaviorTreeAssetPath));
		
	if (IsValid(BehaviorTree))
		Cast<AEnemyController>(GetController())->RunBehaviorTree(BehaviorTree);

	
	// �ִ� �ν��Ͻ� Ŭ���� ����
	GetMesh()->SetAnimInstanceClass(EnemyData->AnimClass);
}
