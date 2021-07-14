// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Enum/PartsType.h"

#include "EquipItemInfo.generated.h"


USTRUCT(BlueprintType)
struct MYACTIONRPG_API FEquipItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
	EPartsType PartsType;

	// Mesh ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FSoftObjectPath MeshPath;

	// �Բ� ���Ǵ� Mesh ���
	/// - �尩 : ���� �տ� �����Ǵ� �尩 Mesh ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FSoftObjectPath SetMeshPath;
};
