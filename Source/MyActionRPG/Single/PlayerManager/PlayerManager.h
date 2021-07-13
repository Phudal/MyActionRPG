// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "Single/PlayerManager/PlayerInventory/PlayerInventory.h"

#include "Struct/CharacterClassInfo/CharacterClassInfo.h"

#include "PlayerManager.generated.h"



UCLASS()
class MYACTIONRPG_API UPlayerManager final : public UManagerClass
{
	GENERATED_BODY()

private:
	class UDataTable* DT_CharacterClassInfo;
	class UDataTable* DT_EquipItemInfo;

private:
	UPROPERTY()
	UPlayerInventory* PlayerInventory;

	UPROPERTY()
	class ABasePlayerController* PlayerController;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	//UPROPERTY()
	//FPlayerCharacterInfo PlayerInfo
	
public:
	virtual void InitManagerClass() override;
	virtual void ShutdownManagerClass() override;
};
