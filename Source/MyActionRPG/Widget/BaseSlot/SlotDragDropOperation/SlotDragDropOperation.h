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
	// �巡�׸� ���۽�Ų ���� ��ü�� ��Ÿ��
	class UBaseSlot* OriginatedDragSlot;
};
