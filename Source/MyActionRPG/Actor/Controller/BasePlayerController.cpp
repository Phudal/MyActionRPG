// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/BasePlayerController.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"



ABasePlayerController::ABasePlayerController()
{
	// TODO ���� ��Ʈ�ѷ� �߰�

	// TODO Ŀ�ǵ� ���� �߰�

	// TODO PlayerBehaviorBroadCast, WndToggler �߰�

	DefaultInputMode = EInputModeType::IM_GameOnly;
	bDefaultCursorVisibility = false;
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// InputComponent->BindAction(TEXT())
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Log, TEXT("BasePlayerController OnPossess"));
	
	GetManager(UPlayerManager)->RegisterPlayer(this, Cast<APlayerCharacter>(InPawn));
}
