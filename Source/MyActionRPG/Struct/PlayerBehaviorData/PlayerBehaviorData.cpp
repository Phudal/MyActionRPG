// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/PlayerBehaviorData/PlayerBehaviorData.h"

FPlayerBehaviorData::FPlayerBehaviorData(EPlayerBehavior::Type behavior) :
	FPlayerBehaviorData(behavior, FName(), 0)
{
}

FPlayerBehaviorData::FPlayerBehaviorData(EPlayerBehavior::Type behavior, FString stringData) :
	FPlayerBehaviorData(behavior, FName(), 0)
{
}

FPlayerBehaviorData::FPlayerBehaviorData(EPlayerBehavior::Type behavior, FName code, int32 count)
{
	Behavior = behavior;
	Code = code;
	Count = count;
	StringData = FString();
}
