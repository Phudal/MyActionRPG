// Fill out your copyright notice in the Description page of Project Settings.


#include "Single/GameInstance/RPGGameInst.h"

#include "Single/PlayerManager/PlayerManager.h"

void URPGGameInst::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassIntance = NewObject<UManagerClass>(this, managerClass,
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
	// 생성된 객체를 GC 가 해제하지 못하도록 함

	managerClassIntance->InitManagerClass();

	ManagerClasses.Add(managerClass->GetName(), managerClassIntance);
}

void URPGGameInst::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("Before Register PlayerManager - Init"));
	RegisterManagerClass(UPlayerManager::StaticClass());
	UE_LOG(LogTemp, Log, TEXT("After Register PlayerManager - Init"));
}

void URPGGameInst::Shutdown()
{
	UE_LOG(LogTemp, Log, TEXT("Shutdown"));
	for (auto pair : ManagerClasses)
	{
		// nullptr 확인
		if (!pair.Value)
			return;

		// 해당 객체가 GC에 의해 해제된 객체인지 확인
		if (!pair.Value->IsValidLowLevel())
			return;

		pair.Value->ShutdownManagerClass();

		// 객체 소멸
		pair.Value->ConditionalBeginDestroy();
	}
	ManagerClasses.Empty();

	Super::Shutdown();
}
