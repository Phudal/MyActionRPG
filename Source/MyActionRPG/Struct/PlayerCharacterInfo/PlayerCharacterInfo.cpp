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
		// �⺻ ��� ������ ������ ����
		FString contextString;
		FEquipItemInfo* defaultEquipmentItemInfo =
			dt_EquipmentItemInfo->FindRow<FEquipItemInfo>(defaultEquipItemCode, contextString);

		// ������ ������ ã�� ���ߴٸ�
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
