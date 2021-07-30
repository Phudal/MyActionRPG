// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API USlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	// 드래그를 시작시킨 슬롯 객체를 나타냄
	class UBaseSlot* OriginatedDragSlot;
};
