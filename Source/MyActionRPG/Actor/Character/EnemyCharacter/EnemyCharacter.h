// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "Struct/EnemyData/EnemyData.h"
#include "EnemyCharacter.generated.h"


UCLASS()
class MYACTIONRPG_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private:
	class UDataTable* DT_EnemyData;
	// TSubclassOf<class UEnemyCharacterWidget> CharacterWidgetClass;

private:
	class UBehaviorTree* BehaviorTree;

// protected:
	// class UCharacterWidgetComponent* CharacterWidget;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Code")
	FName EnemyCode;

	// �� ĳ���� ������ ��Ÿ��
	FEnemyData* EnemyData;

public:
	AEnemyCharacter();

public:
	virtual void PossessedBy(AController* NewController) override;

public:
	// �� ĳ���͸� �ʱ�ȭ��
	/// - �� �޼���� BeginPlay() �� ȣ��� �� ȣ���
	void InitializeEnemyCharacter(FName enemyCode);

//public:
//	FORCEINLINE class UCharacterWidgetComponent* GetCharacterWidget() const
//	{
//		return CharacterWidget;
//	}
};
