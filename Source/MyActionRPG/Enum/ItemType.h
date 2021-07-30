// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

// 아이템 타입을 나타낼 때 상요되는 열거 형식
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EtCetera		UMETA(DisplayName = 기타 아이템),
	Comsumption		UMETA(DisplayName = 소비 아이템),
	Equipment		UMETA(DisplayName = 장비 아이템)
};
