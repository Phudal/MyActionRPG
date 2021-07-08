// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/CharacterClassType.h"
#include "CharacterClassInfo.generated.h"

USTRUCT(BlueprintType)
struct MYACTIONRPG_API FCharacterClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ĳ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ŭ����")
	ECharacterClassType ClassType;

	// �⺻���� �����Ǵ� ��� ������ �ڵ���� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "��Ÿ")
	TArray<FName> DefaultEquipItemCodes;
};
