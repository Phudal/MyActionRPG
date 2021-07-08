// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterClassType.generated.h"

UENUM(BlueprintType)
enum class ECharacterClassType : uint8
{
	CLS_ALL = 0 UMETA(DisplayName = "All"),
	CLS_Warrior = 1 UMETA(DisplayName = "Warrior")	
};
