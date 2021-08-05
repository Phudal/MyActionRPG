// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/PlayerCharacterInfo/PlayerCharacterInfo.h"
#include <Struct/EquipItemInfo/EquipItemInfo.h>

FPlayerCharacterInfo::FPlayerCharacterInfo()
{
	// ĳ���� Ŭ���� �ʱ�ȭ
	// TODO - ĳ���� �߰��� �����ؾ���
	CharacterClass = ECharacterClassType::CLS_Warrior;

	// �κ��丮 ����
	InventorySlotCount = 66;

	for (int32 i = 0; i < InventorySlotCount; i++)
		InventoryItemInfos.Add(FItemSlotInfo());

	// �⺻ ��� ���� ����
	DefaultPartsInfos.Add(EPartsType::PT_Head, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Hair, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Beard, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Top, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Bottom, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Glove, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Shoes, FItemSlotInfo());
	DefaultPartsInfos.Add(EPartsType::PT_Weapon, FItemSlotInfo());
	
	// �� ���� ���� ����
	PartsInfos.Add(EPartsType::PT_Head, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Hair, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Beard, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Top, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Bottom, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Glove, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Shoes, FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Weapon, FItemSlotInfo());

	// TODO -  �׽�Ʈ�� �ڵ�
	Silver = 10000;
	//InventoryItemInfos[1] = (FItemSlotInfo(FName(TEXT("12001")), 1));
	//InventoryItemInfos[12] = (FItemSlotInfo(FName(TEXT("12002")), 1));
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

TTuple<FItemSlotInfo, bool> FPlayerCharacterInfo::GetEquippedItemSlotInfo(EPartsType partsType,
	bool* out_bReturnedAvailableData) const
{
	// Map �� �߰��� ������� Ȯ��
	/// - PartsInfos �� DefaultPartsInfos �� Key �� partsType ���� �� ��Ұ� �������� �ʴ´ٸ� ���������� ��
	/// - partsType �� PT_LGlove�� PT_RGlove �� ���޵Ǿ� �� �޼��尡 �۵��ϴ� ���� �����ϱ� ���� �ۼ���
	if (!PartsInfos.Contains(partsType) && !DefaultPartsInfos.Contains(partsType))
	{
		UE_LOG(LogTemp, Error, TEXT("FPlayerCharacterInfo.cpp :: %d LINE :: (EPartsType)[%d] is not AvaildablePartsType!"),
			__LINE__, static_cast<uint8>(partsType));

		if (out_bReturnedAvailableData)
			*out_bReturnedAvailableData = false;

		return MakeTuple(FItemSlotInfo(), false);
	}

	// �⺻ ��� ����
	FItemSlotInfo defaultEquipItemInfo = DefaultPartsInfos[partsType];

	// ������ ��� ����
	FItemSlotInfo equippedItemSlotInfo = PartsInfos[partsType];

	// ������ ��� ���ٸ�
	if (equippedItemSlotInfo.IsEmpty())
	{
		if (out_bReturnedAvailableData)
			*out_bReturnedAvailableData = true;

		// �⺻ ��� ���� ��ȯ
		return MakeTuple(defaultEquipItemInfo, true);
	}

	// �������� ��� �ִٸ�
	else
	{
		if (out_bReturnedAvailableData)
			*out_bReturnedAvailableData = true;

		// ������ ��� ���� ��ȯ
		return MakeTuple(equippedItemSlotInfo, false);		
	}
}

TMap<EPartsType, TTuple<FItemSlotInfo, bool>> FPlayerCharacterInfo::GetAllEquippedItemSlotInfo() const
{
	TMap<EPartsType, TTuple<FItemSlotInfo, bool>> returnValue;

	// PartsInfos �� ��� �Ҵ��� �̷������ �ʾҴ��� Ȯ����
	if (PartsInfos.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacterInfo.cpp :: %d LINE :: PartsInfos.Num() is zero!"),
			__LINE__);
	}

	else
	{
		// ã���� �ϴ� ���� Ÿ�Ե��� �迭�� ������
		TArray<EPartsType> partsKeys;
		{
			partsKeys.Add(EPartsType::PT_Hair);
			partsKeys.Add(EPartsType::PT_Head);
			partsKeys.Add(EPartsType::PT_Beard);
			partsKeys.Add(EPartsType::PT_Top);
			partsKeys.Add(EPartsType::PT_Bottom);
			partsKeys.Add(EPartsType::PT_Glove);
			partsKeys.Add(EPartsType::PT_Shoes);
			partsKeys.Add(EPartsType::PT_Weapon);
		}

		for (EPartsType partsKey : partsKeys)
		{
			// ���� ������ ��� ������ ���� ������ ����
			bool bReturnedAvailableData = false; // ��ȯ���� �����Ͱ� ��ȿ�� ���������� Ȯ���ϱ� ���� ����
			TTuple<FItemSlotInfo, bool> equippedItemSlotInfo =
				GetEquippedItemSlotInfo(partsKey, &bReturnedAvailableData);

			// �������� ������ �ƴ϶�� �������� ����
			if (!bReturnedAvailableData)
				continue;;

			// ��� �߰�
			returnValue.Add(partsKey, equippedItemSlotInfo);
		}
	}
	return returnValue;
}
