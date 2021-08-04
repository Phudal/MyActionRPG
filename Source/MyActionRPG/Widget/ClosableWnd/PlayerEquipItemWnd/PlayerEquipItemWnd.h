// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Enum/PartsType.h"

#include "PlayerEquipItemWnd.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API UPlayerEquipItemWnd : public UClosableWnd
{
	GENERATED_BODY()

private:
	// â�� ǥ�õǴ� ���Ե�
	TMap<EPartsType, class UPlayerEquipSlot*> EquipSlots;

protected:
	virtual void NativeConstruct() override;
	
public:
	// ���� ���Ե��� ������
	void UpdatePartsSlot();
	
public:
	FORCEINLINE class UPlayerEquipSlot* GetPlayerEquipSlot(EPartsType partsTypes) const
	{
		if (!EquipSlots.Contains(partsTypes))
			return nullptr;
		
		return EquipSlots[partsTypes];
	}
};
