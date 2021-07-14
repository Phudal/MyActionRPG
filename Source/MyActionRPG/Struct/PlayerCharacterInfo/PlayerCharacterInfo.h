// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enum/CharacterClassType.h"
#include "Enum/PartsType.h"

#include "Engine/UserDefinedStruct.h"
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

	
	FPlayerCharacterInfo();

	// �⺻ ��� �����۵� �ʱ�ȭ
	void InitializeDefaultEquipmentItems(
		TArray<FName>& defaultEquipmentItemCodes, const class UDataTable* dt_EquipmentItemInfo);

	// TODO
	// ��� ������ ������ ����
};
