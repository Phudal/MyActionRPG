// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "MyActionRPG.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

#include "AnimInstance/PlayerCharacterAnimInst/PlayerCharacterAnimInst.h"

#include "Component/CharacterMovementHelper/CharacterMovementHelperComponent.h"
#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Component/SkillControllerComponent/SkillControllerComponent.h"

#include "Enum/Team.h"

//#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_TEST_MESH(
		TEXT("SkeletalMesh'/Game/Resources/PlayerCharacter/GKnight/Meshes/SK_GothicKnight_VF.SK_GothicKnight_VF'"));

	if (SK_TEST_MESH.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_TEST_MESH.Object);

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInst> BP_PLAYER_CHARACTER_ANIM_INST(
		TEXT("AnimBlueprint'/Game/Blueprints/AnimInstance/BP_PlayerCharacter.BP_PlayerCharacter_C'"));

	if (BP_PLAYER_CHARACTER_ANIM_INST.Succeeded())
		BP_PlayerCharacterAnimInst = BP_PLAYER_CHARACTER_ANIM_INST.Class;

	
	// 컴포넌트 생성
	skillController = CreateDefaultSubobject<USkillControllerComponent>(TEXT("SKILL_CONTROLLER"));
	CharacterMovementHelper = CreateDefaultSubobject<UCharacterMovementHelperComponent>(TEXT("MOVEMENT_HELPER"));
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetConstraintAspectRatio(true);
	
	HeadMesh = GetMesh();
	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HAIR_MESH"));
	BeardMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BEARD_MESH"));
	TopMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TOP_MESH"));
	BottomMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BOTTOM_MESH"));
	RGloveMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RGLOVE_MESH"));
	LGloveMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LGLOVE_MESH"));
	ShoesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SHOES_MESH"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON_MESH"));

	{
		Parts.Empty();
		Parts.Add(EPartsType::PT_Hair, HairMesh);
		Parts.Add(EPartsType::PT_Beard, BeardMesh);
		Parts.Add(EPartsType::PT_Head, HeadMesh);
		Parts.Add(EPartsType::PT_Top, TopMesh);
		Parts.Add(EPartsType::PT_Bottom, BottomMesh);
		Parts.Add(EPartsType::PT_RGlove, RGloveMesh);
		Parts.Add(EPartsType::PT_LGlove, LGloveMesh);
		Parts.Add(EPartsType::PT_Shoes, ShoesMesh);
		Parts.Add(EPartsType::PT_Weapon, WeaponMesh);
	}

	// Skeletal Mesh Settings
	{
		BeardMesh->SetupAttachment(HeadMesh);
		TopMesh->SetupAttachment(HeadMesh);
		BottomMesh->SetupAttachment(HeadMesh);
		RGloveMesh->SetupAttachment(HeadMesh);
		LGloveMesh->SetupAttachment(HeadMesh);
		ShoesMesh->SetupAttachment(HeadMesh);
		WeaponMesh->SetupAttachment(HeadMesh);

		HairMesh->SetupAttachment(HeadMesh, FName(TEXT("HAIR")));
	}

	// TODO
	// PlayerInteractr

	// Spring Arm Component 를 루트 컴포넌트에 추가
	SpringArm->SetupAttachment(GetRootComponent());

	// Camera Component를 SpringArm 컴포넌트에 추가
	Camera->SetupAttachment(SpringArm);

	// 컨트롤러의 회전 값을 SpringArm Component 회전 값으로 사용함
	SpringArm->bUsePawnControlRotation = true;

	// 컨트롤러의 회전 중 Yaw, Pitch 회전을 사용
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritPitch = true;

	// SpringArm 오프셋을 설정
	SpringArm->TargetOffset = FVector::UpVector * 70.0f;

	// 캐릭터의 기본 위치 / 회전 설정
	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// 이 액터의 회전이 컨트롤러의 Yaw 회전을 사용하지 않도록 함
	bUseControllerRotationYaw = false;

	// 이동하는 방향으로 캐릭터를 회전시킴
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도를 지정함
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	// Anim Instance 클래스 설정
	GetMesh()->SetAnimClass(BP_PlayerCharacterAnimInst);

	Tags.Add(PLAYER_ACTOR_TAG);

	// 팀을 설정함
	SetGenericTeamId(ETeam::Player);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,
		GetCharacterMovementHelper(), &UCharacterMovementHelperComponent::RunKeyPressed);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released,
		GetCharacterMovementHelper(), &UCharacterMovementHelperComponent::RunKeyReleased);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		GetCharacterMovementHelper(), &UCharacterMovementHelperComponent::JumpKeyPressed);

	//PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed,
	//	GetPlayerInteract(), &UCharacterMovementHelperComponent::Try);

	PlayerInputComponent->BindAction(TEXT("RegularAttack"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::RegularAttack);

	
	PlayerInputComponent->BindAxis(TEXT("MouseWheel"),
		SpringArm, &UZoomableSpringArmComponent::ZoomCamera);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"),
		GetCharacterMovementHelper(), &UCharacterMovementHelperComponent::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"),
		GetCharacterMovementHelper(), &UCharacterMovementHelperComponent::InputVertical);
}

void APlayerCharacter::InitializeMeshs()
{
	// HeadMesh 의 정보를 다른 Skeletal Mehs 들이 받아서 공유도록 함
	// HairMesh->SetMasterPoseComponent(HeadMesh);
	BeardMesh->SetMasterPoseComponent(HeadMesh);
	TopMesh->SetMasterPoseComponent(HeadMesh);
	BottomMesh->SetMasterPoseComponent(HeadMesh);
	RGloveMesh->SetMasterPoseComponent(HeadMesh);
	LGloveMesh->SetMasterPoseComponent(HeadMesh);
	ShoesMesh->SetMasterPoseComponent(HeadMesh);
	WeaponMesh->SetMasterPoseComponent(HeadMesh);

	HeadMesh->SetAnimClass(BP_PlayerCharacterAnimInst);
	// 만약 BaseSkeletalMesh(HeadMesh) 가 사용하는 Skeleton 이 변경될 경우
	// SetMasterPoseComponent 에 전달한 Mesh 와의 연결을 끊고, 
	// ㄴ (Slave->SetMasterPoseComponent(nullptr))
	// BaseSkeletalMesh 의 Skeletal Mesh 애셋을 설정한 뒤
	// SetMasterPoseComponent 로 재연결 시켜야 함.
}

void APlayerCharacter::RegularAttack()
{
	skillController->RequestSkill(FName(TEXT("1000")));

	UE_LOG(LogTemp, Log, TEXT("RequestSkill"));
}
