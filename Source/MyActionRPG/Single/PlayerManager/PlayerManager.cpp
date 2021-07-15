// Fill out your copyright notice in the Description page of Project Settings.


#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Actor/Controller/BasePlayerController.h"

#include "Struct/CharacterClassInfo/CharacterClassInfo.h"

UPlayerManager::UPlayerManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTER_CLASS_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_CharacterClassInfo.DT_CharacterClassInfo'"));

	if (DT_CHARACTER_CLASS_INFO.Succeeded())
		DT_CharacterClassInfo = DT_CHARACTER_CLASS_INFO.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EQUIP_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_EquipItemInfo.DT_EquipItemInfo'"));

	if (DT_EQUIP_ITEM_INFO.Succeeded())
		DT_EquipItemInfo = DT_EQUIP_ITEM_INFO.Object;
}

void UPlayerManager::RegisterPlayer(ABasePlayerController* newPlayerController, APlayerCharacter* newPlayerCharacter)
{
	UE_LOG(LogTemp, Log, TEXT("Begin RegisterPlayer - PlayerManager"));
	
	PlayerController = newPlayerController;
	PlayerCharacter = newPlayerCharacter;

	UE_LOG(LogTemp, Log, TEXT("After RegisterPlayer - PlayerManager"));
}


void UPlayerManager::InitManagerClass()
{
	// 플레이어 인벤토리를 StaticClass()로 참조 후 등록
	PlayerInventory = NewObject<UPlayerInventory>(this, UPlayerInventory::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
}

void UPlayerManager::ShutdownManagerClass()
{
	// PlayerInventory가 유효하지 않다면 return
	if (!PlayerInventory->IsValidLowLevel())
		return;

	// 객체를 파괴하도록 함
	// ConditionalBeginDestroy : 객체가 파괴되기 전에 호출되는 함수
	PlayerInventory->ConditionalBeginDestroy();
}

void UPlayerManager::InitializePlayerCharacter()
{	
	// 캐릭터 정보
	FPlayerCharacterInfo* playerCharacterInfo = GetPlayerInfo();

	//// 클래스 정보를 얻음
	//FName classKey = FName(*FString::FromInt(
	//	static_cast<uint32>(playerCharacterInfo->CharacterClass)));

	//FString contextString;
	//FCharacterClassInfo* newClassInfo = DT_CharacterClassInfo->FindRow<FCharacterClassInfo>(classKey, contextString);

	//// 기본 장비 초기화
	//playerCharacterInfo->InitializeDefaultEquipmentItems(
	//	newClassInfo->DefaultEquipItemCodes, DT_EquipItemInfo);

	//// 장착된 모든 파츠 Mesh를 비움
	//for (TPair<EPartsType, USkeletalMeshComponent*> partsInfo : GetPlayerCharacter()->GetParts())
	//{
	//	if (partsInfo.Key == EPartsType::PT_LGlove ||
	//		partsInfo.Key == EPartsType::PT_RGlove)
	//	{
	//		// playerCharacterInfo->PartInfos[EPartsType::PT_LGlove].Clear();
	//	}
	//	//else
	//		//playerCharacterInfo->PartsInfo[partsInfo.Key].Clear();
	//	//partsInfo.Value->SetSkeletalMesh(nullptr);
	//}

	//// GetPlayerInventory()->UpdateCharacterVisual();
	//GetPlayerCharacter()->InitializeMeshs();
}
