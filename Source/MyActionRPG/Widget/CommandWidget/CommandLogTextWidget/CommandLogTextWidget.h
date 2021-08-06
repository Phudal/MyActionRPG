// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enum/CommandLogType.h"

#include "CommandLogTextWidget.generated.h"


UCLASS()
class MYACTIONRPG_API UCommandLogTextWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Log;

public:
	void SetLogLevel(ECommandLog::Type logLevel);

	void SetText(FString str);
	void SetText(FText text);
};
