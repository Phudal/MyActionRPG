// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/InputModeType.h"

#include "WidgetControllerWidget.generated.h"


UCLASS()
class MYACTIONRPG_API UWidgetControllerWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// TSubclassOf<class UMessageBoxWnd> BP_MessageBoxWnd;
	TSubclassOf<UUserWidget> BP_MessageBoxBackground;
};
