// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartsType.generated.h"


UENUM(BlueprintType)
enum class EPartsType : uint8
{
	PT_Hair		UMETA(DisplayName = "���"),
	PT_Head		UMETA(DisplayName = "�Ӹ�"),
	PT_Beard	UMETA(DisplayName = "����"),
	PT_Top		UMETA(DisplayName = "����"),
	PT_Bottom	UMETA(DisplayName = "����"),
	PT_Glove	UMETA(DisplayName = "�尩"),
	PT_LGlove	UMETA(DisplayName = "�尩L"),
	PT_RGlove	UMETA(DisplayName = "�尩R"),
	 								
	PT_Shoes	UMETA(DisplayName = "�Ź�"),
	PT_Weapon	UMETA(DisplayName = "����")	
};
