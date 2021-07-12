// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CharacterMovementHelper/CharacterMovementHelperComponent.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UCharacterMovementHelperComponent::UCharacterMovementHelperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;
}


// Called when the game starts
void UCharacterMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// 공중에서 캐릭터를 80% 제어 가능하도록 함
	PlayerCharacter->GetCharacterMovement()->AirControl = 0.8f;

	// 캐릭터가 받는 중력 설정
	PlayerCharacter->GetCharacterMovement()->GravityScale = 2.5f;

	// 점프 초기 가속력 설정
	PlayerCharacter->GetCharacterMovement()->JumpZVelocity = 1000.0f;
}


// Called every frame
void UCharacterMovementHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UCharacterMovementHelperComponent::IsInAir() const
{
	return IsValid(PlayerCharacter) ?
		PlayerCharacter->GetCharacterMovement()->IsFalling() : true;
}

void UCharacterMovementHelperComponent::RunKeyPressed()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void UCharacterMovementHelperComponent::RunKeyReleased()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void UCharacterMovementHelperComponent::JumpKeyPressed()
{
	PlayerCharacter->Jump();
}

void UCharacterMovementHelperComponent::InputHorizontal(float axis)
{
	// 컨트롤러 회전 중 Yaw 회전만을 저장함
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 오른쪽 방향을 저장
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix : 회전된 좌표계 정보를 저장하는 행렬을 나타냅니다.
	// GetUnitAxis(EAxis) : EAxis 축으로의 방향을 반환합니다.

	PlayerCharacter->AddMovementInput(rightVector, axis);
}

void UCharacterMovementHelperComponent::InputVertical(float axis)
{
	// 컨트롤러 회전 중 Yaw 회전만을 저장함
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 앞 방향 저장
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	PlayerCharacter->AddMovementInput(forwardVector, axis);
}

