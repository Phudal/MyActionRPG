// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Single/ManagerClass/ManagerClass.h"

#include "Serialization/JsonWriter.h"
#include "JsonObjectConverter.h"

#include "RPGGameInst.generated.h"


#ifndef GAME_INST
#define GAME_INST
#define GetGameInst(worldContextObj) (Cast<URPGGameInst>(worldContextObj->GetGameInstance()))
#endif



UCLASS()
class MYACTIONRPG_API URPGGameInst : public UGameInstance
{
	GENERATED_BODY()

private:
	// 등록한 매니저 클래스 인스턴스를 저장
	TMap<FString, UManagerClass*> ManagerClasses;

private:
	// ManagerClass를 등록
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public:
	virtual void Init() override;
	virtual void Shutdown() override;

public :
	// 등록한 ManagerClass를 얻음
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{
		UE_LOG(LogTemp, Log, TEXT("GetManagerClass"));
		return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]);
	}
	
	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{
		UE_LOG(LogTemp, Log, TEXT("GetManagerClass<FStreamableManager>"));
		return &UAssetManager::GetStreamableManager();
	}
};
