// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartsType.generated.h"


UENUM(BlueprintType)
enum class EPartsType : uint8
{
	PT_Hair		UMETA(DisplayName = "Hair"),
	PT_Head		UMETA(DisplayName = "Head"),
	PT_Beard	UMETA(DisplayName = "Beard"),
	PT_Top		UMETA(DisplayName = "Top"),
	PT_Bottom	UMETA(DisplayName = "Bottom"),
	PT_Glove	UMETA(DisplayName = "Glove"),
	PT_LGlove	UMETA(DisplayName = "LGlove"),
	PT_RGlove	UMETA(DisplayName = "RGlove"),
	 								
	PT_Shoes	UMETA(DisplayName = "Shoes"),
	PT_Weapon	UMETA(DisplayName = "Weapon")	
};
