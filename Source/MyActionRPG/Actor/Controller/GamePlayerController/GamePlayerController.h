// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Controller/BasePlayerController.h"
#include "GamePlayerController.generated.h"


UCLASS()
class MYACTIONRPG_API AGamePlayerController : public ABasePlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	// MouseX, MouseY 입력에 바인딩될 메서드
	void MouseXInput(float axis);
	void MouseYInput(float axis);
};
