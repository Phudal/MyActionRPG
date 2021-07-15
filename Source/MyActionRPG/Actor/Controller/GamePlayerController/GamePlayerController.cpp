// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/GamePlayerController/GamePlayerController.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"


void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction(TEXT("OpenPlayerInventoryWnd"), EInputEvent::IE_Pressed,
	//	GetWndToggler)

	InputComponent->BindAxis(TEXT("MouseX"), this, &AGamePlayerController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &AGamePlayerController::MouseYInput);
}

void AGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Log, TEXT("GamePlayerController OnPossess"));
	
	// - TODO - Test �� Code
	/// ���߿� ĳ���� Ŭ������ �߰��Ǵ� ��� ���ŵǾ�� ��
	GetManager(UPlayerManager)->InitializePlayerCharacter();
	// --------------------------------------------------------------///	
}

void AGamePlayerController::MouseXInput(float axis)
{
	AddYawInput(axis);
}

void AGamePlayerController::MouseYInput(float axis)
{
	AddPitchInput(axis);
}
