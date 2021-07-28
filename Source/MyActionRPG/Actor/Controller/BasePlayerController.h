// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/InputModeType.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/// 있어야 할 property
/// BP_WidgetControllerWidget
/// BP_CommandWidget
///
/// WidgetControllerWidget 
/// CommandWidget
/// PlayerBehaviorBroadcastComponent
/// WndTogglerComponent
/// DefaultInputMode

UCLASS()
class MYACTIONRPG_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

//private:
	// TSubclassOf<class UWidgetControllerWidget> BP_WidgetController;

protected:
	EInputModeType DefaultInputMode;
	bool bDefaultCursorVisibility;
	
public:
	ABasePlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	FORCEINLINE EInputModeType GetDefaultInputMode() const
	{
		return DefaultInputMode;
	}

	FORCEINLINE bool GetDefaultCursorVisibility() const
	{
		return bDefaultCursorVisibility;
	}

	FORCEINLINE void SetInputModeFromNewInputModeType(EInputModeType newInputMode)
	{
		switch (newInputMode)
		{
		case EInputModeType::IM_GameOnly:
			SetInputMode(FInputModeGameOnly());
			break;
		case EInputModeType::IM_UIOnly:
			SetInputMode(FInputModeUIOnly());
			break;
		case EInputModeType::IM_GameAndUI:
			SetInputMode(FInputModeGameAndUI());
			break;
		}
	}
	
	// TODO 윈도우 조작 추가, 카메라 뷰 변경 추가

	
	FORCEINLINE void ChangeInputModeToDefault()
	{
		switch (DefaultInputMode)
		{
		case EInputModeType::IM_GameOnly: 
			SetInputMode(FInputModeGameOnly());
			break;
			
		case EInputModeType::IM_UIOnly:
			SetInputMode(FInputModeUIOnly());
			break;

		case EInputModeType::IM_GameAndUI:
			SetInputMode(FInputModeGameAndUI());
			break;
		}
	}
	
};
