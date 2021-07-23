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

	// 적 캐릭터 정보를 나타냄
	FEnemyData* EnemyData;

public:
	AEnemyCharacter();

public:
	virtual void PossessedBy(AController* NewController) override;

public:
	// 적 캐릭터를 초기화함
	/// - 이 메서드는 BeginPlay() 가 호출될 때 호출됨
	void InitializeEnemyCharacter(FName enemyCode);

//public:
//	FORCEINLINE class UCharacterWidgetComponent* GetCharacterWidget() const
//	{
//		return CharacterWidget;
//	}
};
