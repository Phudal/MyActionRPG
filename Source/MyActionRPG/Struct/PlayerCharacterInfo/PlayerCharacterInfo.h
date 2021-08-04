// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/CharacterClassType.h"
#include "Enum/PartsType.h"

#include "Engine/UserDefinedStruct.h"
#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "PlayerCharacterInfo.generated.h"

/// �־�� �� �� ���
/// 
/// ĳ���� Ŭ���� Ÿ��
/// ĳ���� ����
/// �κ��丮 ���� ����
/// �������� ������ ����
/// �⺻ ���� ������ ����
/// ���� ������ ����
/// ������
///
/// �������� ����Ʈ ���
/// �Ϸ��� ����Ʈ ���


USTRUCT()
struct MYACTIONRPG_API FPlayerCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public:
	// ĳ���� Ŭ���� Ÿ��
	UPROPERTY()
	ECharacterClassType CharacterClass;

	// ĳ���� ����
	UPROPERTY()
	int32 CharacterLevel;

	// �κ��丮 ���� ����
	UPROPERTY()
	int32 InventorySlotCount;

	// �������� ������ ����
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// �⺻ ���� ������ ����
	UPROPERTY()
	TMap<EPartsType, FItemSlotInfo> DefaultPartsInfos;


	// ���� ������ ����
	UPROPERTY()	
	TMap<EPartsType, FItemSlotInfo> PartsInfos;

	// ������
	UPROPERTY()
	int32 Silver;
	
	
	FPlayerCharacterInfo();

	// �⺻ ��� �����۵� �ʱ�ȭ
	void InitializeDefaultEquipmentItems(
		TArray<FName>& defaultEquipmentItemCodes, const class UDataTable* dt_EquipmentItemInfo);

	
	// ��� ������ ������ ����
	/// - Return : <��� �Ɵ�� ���� ����, ��ȯ���� ���� ������ �⺻ ��� ������ ����>
	TTuple<FItemSlotInfo, bool> GetEquippedItemSlotInfo(EPartsType partsType, bool* out_bReturnedAvailableData = nullptr) const;

	// ��� ��� ������ ������ ����
	TMap<EPartsType, TTuple<FItemSlotInfo, bool>> GetAllEquippedItemSlotInfo() const;

	
	// TODO
	// ���� ����Ʈ�� �߰���
	// void AddProgessQuest(FName newQuestCode, FQ)
	
};
