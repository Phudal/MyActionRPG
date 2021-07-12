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

	// ���߿��� ĳ���͸� 80% ���� �����ϵ��� ��
	PlayerCharacter->GetCharacterMovement()->AirControl = 0.8f;

	// ĳ���Ͱ� �޴� �߷� ����
	PlayerCharacter->GetCharacterMovement()->GravityScale = 2.5f;

	// ���� �ʱ� ���ӷ� ����
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
	// ��Ʈ�ѷ� ȸ�� �� Yaw ȸ������ ������
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� ������ ������ ����
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix : ȸ���� ��ǥ�� ������ �����ϴ� ����� ��Ÿ���ϴ�.
	// GetUnitAxis(EAxis) : EAxis �������� ������ ��ȯ�մϴ�.

	PlayerCharacter->AddMovementInput(rightVector, axis);
}

void UCharacterMovementHelperComponent::InputVertical(float axis)
{
	// ��Ʈ�ѷ� ȸ�� �� Yaw ȸ������ ������
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� �� ���� ����
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	PlayerCharacter->AddMovementInput(forwardVector, axis);
}

