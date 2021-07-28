// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/InputModeType.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/// �־�� �� property
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
	
	// TODO ������ ���� �߰�, ī�޶� �� ���� �߰�

	
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
