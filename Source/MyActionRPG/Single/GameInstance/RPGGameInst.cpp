// Fill out your copyright notice in the Description page of Project Settings.


#include "Single/GameInstance/RPGGameInst.h"

#include "Single/PlayerManager/PlayerManager.h"

void URPGGameInst::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassIntance = NewObject<UManagerClass>(this, managerClass,
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
	// ������ ��ü�� GC �� �������� ���ϵ��� ��

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
		// nullptr Ȯ��
		if (!pair.Value)
			return;

		// �ش� ��ü�� GC�� ���� ������ ��ü���� Ȯ��
		if (!pair.Value->IsValidLowLevel())
			return;

		pair.Value->ShutdownManagerClass();

		// ��ü �Ҹ�
		pair.Value->ConditionalBeginDestroy();
	}
	ManagerClasses.Empty();

	Super::Shutdown();
}
