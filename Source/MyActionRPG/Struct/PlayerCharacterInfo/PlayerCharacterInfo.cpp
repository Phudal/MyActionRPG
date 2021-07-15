// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/PlayerCharacterInfo/PlayerCharacterInfo.h"
#include <Struct/EquipItemInfo/EquipItemInfo.h>

FPlayerCharacterInfo::FPlayerCharacterInfo()
{
}

void FPlayerCharacterInfo::InitializeDefaultEquipmentItems(
	TArray<FName>& defaultEquipmentItemCodes,
	const UDataTable* dt_EquipmentItemInfo)
{
	for (FName defaultEquipItemCode : defaultEquipmentItemCodes)
	{
		// 기본 장비 아이템 정보를 얻음
		FString contextString;
		FEquipItemInfo* defaultEquipmentItemInfo =
			dt_EquipmentItemInfo->FindRow<FEquipItemInfo>(defaultEquipItemCode, contextString);

		// 아이템 정보를 찾지 못했다면
		if (defaultEquipmentItemInfo == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerCharacterInfo.cpp :: %d LINE :: defaultEquipItemCode(%s) is not valid!"),
				__LINE__, *defaultEquipItemCode.ToString());

			continue;
		}

		// TODO
		// DefaultParts
	}
}
