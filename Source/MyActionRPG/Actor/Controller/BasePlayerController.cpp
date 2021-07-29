// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/BasePlayerController.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/CanvasPanelSlot.h"



ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UWidgetControllerWidget> BP_WIDGET_CONTROLLER_WIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WidgetController/BP_WidgetController.BP_WidgetController_C'"));

	if (BP_WIDGET_CONTROLLER_WIDGET.Succeeded())
		BP_WidgetController = BP_WIDGET_CONTROLLER_WIDGET.Class;

	else
	{
		UE_LOG(LogTemp, Error, TEXT("BasePlayerController.cpp :: %d LINE :: BP_WIDGET_CONTROLLER_WIDGET is not loaded!"),
			__LINE__);
	}

	
	// TODO 커맨드 위젯 추가

	// TODO PlayerBehaviorBroadCast, WndToggler 추가

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

	// WidgetControllerWidget 생성 후 초기화, 뷰포트에 추가
	WidgetControllerWidget = CreateWidget<UWidgetControllerWidget>(this, BP_WidgetController);
	WidgetControllerWidget->InitializeWidgetControllerWidget(this);
	WidgetControllerWidget->AddToViewport();
}
