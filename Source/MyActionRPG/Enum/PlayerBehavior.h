// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace EPlayerBehavior
{
	enum Type: uint8
	{
		// Default
		BH_None,

		// Item Event
		BH_GetItem,

		// Quest Event
		BH_StartQuest,
		BH_FinishQuest
	};
}
