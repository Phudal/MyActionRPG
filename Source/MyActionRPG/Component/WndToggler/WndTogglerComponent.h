// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ActorComponent.h"
#include "WndTogglerComponent.generated.h"


DECLARE_DELEGATE(FToggleEvent)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONRPG_API UWndTogglerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// ��� ������ ������ ������� �� ȣ���� �븮��
	TMap<TSubclassOf<class UObject>, FToggleEvent> ToggleEvents;

public:
	template<typename T>
	FORCEINLINE void RegisterToggleEvent(FToggleEvent toggleEvent)
	{
		ToggleEvents.Add(T::StaticClass(), toggleEvent);
	}

	template<typename T>
	FORCEINLINE void ToggleWnd()
	{
		if (!ToggleEvents.Contains(T::StaticClass()))
			return;

		UE_LOG(LogTemp, Log, TEXT("ToggleWnd"));
		
		ToggleEvents[T::StaticClass()].ExecuteIfBound();
	}

};
