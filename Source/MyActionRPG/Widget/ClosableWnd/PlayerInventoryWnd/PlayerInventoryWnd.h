// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "PlayerInventoryWnd.generated.h"


UCLASS()
class MYACTIONRPG_API UPlayerInventoryWnd : public UClosableWnd
{
	GENERATED_BODY()

//private:
//	TSubclassOf<class UPlayerInventoryItemSlot>

public:
	// 인벤토리 아이템 슬롯들을 갱신함
	void UpdateInventoryItemSlots();
};
