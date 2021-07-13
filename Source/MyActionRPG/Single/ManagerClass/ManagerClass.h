// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerClass.generated.h"

#ifndef MANAGER_INSTANCE
#define MANAGER_INSTANCE
#define GetManager(ManagerClassType) (GetGameInst(GetWorld())->GetManagerClass<ManagerClassType>())

#endif

UCLASS(Abstract)
class MYACTIONRPG_API UManagerClass :
	public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual void InitManagerClass() { };
	FORCEINLINE virtual void ShutdownManagerClass() { };
};
