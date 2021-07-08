// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartsType.generated.h"


UENUM(BlueprintType)
enum class EPartsType : uint8
{
	PT_Hair		UMETA(DisplayName = "헤어"),
	PT_Head		UMETA(DisplayName = "머리"),
	PT_Beard	UMETA(DisplayName = "수염"),
	PT_Top		UMETA(DisplayName = "상의"),
	PT_Bottom	UMETA(DisplayName = "하의"),
	PT_Glove	UMETA(DisplayName = "장갑"),
	PT_LGlove	UMETA(DisplayName = "장갑L"),
	PT_RGlove	UMETA(DisplayName = "장갑R"),
	 								
	PT_Shoes	UMETA(DisplayName = "신발"),
	PT_Weapon	UMETA(DisplayName = "무기")	
};
