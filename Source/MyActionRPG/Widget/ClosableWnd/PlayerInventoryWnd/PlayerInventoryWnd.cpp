//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Widget/ClosableWnd/PlayerInventoryWnd/PlayerInventoryWnd.h"
//
//#include "Single/PlayerManager/PlayerManager.h"
//#include "Single/GameInstance/RPGGameInst.h"
//
//#include "Actor/Controller/GamePlayerController/GamePlayerController.h"
//#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
//
//#include "Widget/BaseSlot/ItemSlot/PlayerInventoryItemSlot/PlayerInventoryItemSlot.h"
//#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"
//
//#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"
//#include "Components/GridPanel.h"
//#include "Components/GridSlot.h"
//#include "Components/TextBlock.h"
//
//
//UPlayerInventoryWnd::UPlayerInventoryWnd(const FObjectInitializer& ObjectInitializer) :
//	Super(ObjectInitializer)
//{		
//	static ConstructorHelpers::FClassFinder<UPlayerInventoryItemSlot> BP_PLAYER_INVENTORY_SLOT(
//		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Slot/BP_PlayerInventoryItemSlot.BP_PlayerInventoryItemSlot_C'"));
//
//	if (BP_PLAYER_INVENTORY_SLOT.Succeeded())
//		BP_PlayerInventoryItemSlot = BP_PLAYER_INVENTORY_SLOT.Class;
//}
//
//void UPlayerInventoryWnd::NativeConstruct()
//{
//	Super::NativeConstruct();
//
//	WndSize = FVector2D(460.0f, 700.0f);
//
//	UE_LOG(LogTemp, Log, TEXT("Before InitializeInventoryWnd"));
//	
//	InitializeInventoryWnd();
//
//	// 소지금 갱신
//	UpdateSilver();
//
//	for (auto itemSlot : ItemSlots)
//	{
//		auto info = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[itemSlot->GetItemSlotIndex()];
//	}
//}
//
//void UPlayerInventoryWnd::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	// GridPanel_ItemSlots.
//}
//
//void UPlayerInventoryWnd::InitializeInventoryWnd()
//{
//#pragma region Create Inventory Slots
//
//	// 플레이어 캐릭터 정보를 얻음
//	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
//
//	// 인벤토리 슬롯 개수를 얻음
//	int32 inventorySlotCount = playerInfo->InventorySlotCount;
//
//	const int32 maxColumCount = 6;
//	int32 currentColumnCount = 0;
//
//	// 인벤토리 슬롯들을 생성함
//	for (int32 i = 0; i < inventorySlotCount; i++)
//	{
//		// 인벤토리 슬롯 생성
//		auto newItemSlot = CreateItemSlot();
//
//		// 슬롯 초기화
//		newItemSlot->InitializeItemSlot(
//			ESlotType::ST_InventorySlot,
//			playerInfo->InventoryItemInfos[i].ItemCode, i);		
//		
//		// 생성한 슬롯을 정렬함
//		UWidgetControllerWidget::SortGridPanelElem(newItemSlot, maxColumCount, currentColumnCount);
//
//		// ItemSlots[i]->AddToViewport();
//		
//		// UE_LOG(LogTemp, Log, TEXT("Item Slot Number - %d"), ItemSlots.Num());
//		UE_LOG(LogTemp, Log, TEXT("Item Slot Number - %d, visible - %s, GetIsEnabled -%s"), GridPanel_ItemSlots->GetChildrenCount(),
//			ItemSlots[i]->IsVisible() ? TEXT("true") : TEXT("false"),
//			ItemSlots[i]->GetIsEnabled() ? TEXT("true") : TEXT("false"));
//
//		//UE_LOG(LogTemp, Log, TEXT("Is in viewport - %s"),
//		//	ItemSlots[i]->IsInViewport() ? TEXT("true") : TEXT("false"));
//
//		
//	}
//
//	UE_LOG(LogTemp, Log, TEXT("number of ItemSltos : %d"), ItemSlots.Num());
//	
//	
//#pragma endregion
//
//#pragma region Lock Camera Zoom
//	// 인벤토리 창이 열리면 카메라 줌을 막음
//	GetManager(UPlayerManager)->GetPlayerCharacter()->GetSpringArm()->SetUseZoom(false);
//
//	// 인벤토리 창이 닫히면 카메라 줌을 사용할 수 있도록 함
//	OnWndClosedEvent.AddLambda([this](UClosableWnd* ClosableWnd)
//		{
//			GetManager(UPlayerManager)->GetPlayerCharacter()->GetSpringArm()->SetUseZoom(true);
//		});
//#pragma endregion 
//}
//
//UPlayerInventoryItemSlot* UPlayerInventoryWnd::CreateItemSlot()
//{
//	// 인벤토리 슬롯을 생성함
//	auto newItemSlot = CreateWidget<UPlayerInventoryItemSlot>(this, BP_PlayerInventoryItemSlot);
//
//	ItemSlots.Add(newItemSlot);
//
//	// GridPanel_ItemSlots 의 자식 위젯으로 추가함
//	GridPanel_ItemSlots->AddChild(newItemSlot);
//
//	// 생성한 인벤토리 슬롯을 반환함
//	return newItemSlot;
//}
//
//void UPlayerInventoryWnd::UpdateSilver()
//{
//	FPlayerCharacterInfo* PlayerCharacterInfo = GetManager(UPlayerManager)->GetPlayerInfo();
//
//	TArray<FItemSlotInfo>& inventoryItemInfos = PlayerCharacterInfo->InventoryItemInfos;
//
//	for (int32 i = 0; i < ItemSlots.Num(); i++)
//	{
//		auto itemSlot = ItemSlots[i];
//
//		itemSlot->SetItemInfo(inventoryItemInfos[i].ItemCode);
//
//		itemSlot->UpdateInventoryItemSlot();
//
//		itemSlot->InitializeItemSlot(ESlotType::ST_InventorySlot, 
//			PlayerCharacterInfo->InventoryItemInfos[i].ItemCode, i);
//	}
//}
//
//void UPlayerInventoryWnd::UpdateInventoryItemSlots()
//{
//	FText silverToText = FText::FromString(FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->Silver));
//	Text_Silver->SetText(silverToText);
//}

#include "PlayerInventoryWnd.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Controller/GamePlayerController/GamePlayerController.h"
#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Widget/BaseSlot/ItemSlot/PlayerInventoryItemSlot/PlayerInventoryItemSlot.h"
#include "Widget/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/TextBlock.h"

UPlayerInventoryWnd::UPlayerInventoryWnd(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UPlayerInventoryItemSlot> BP_PLAYER_INVENTORY_ITEM_SLOT(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Slot/BP_PlayerInventoryItemSlot.BP_PlayerInventoryItemSlot_C'"));
	if (BP_PLAYER_INVENTORY_ITEM_SLOT.Succeeded()) BP_PlayerInventoryItemSlot = BP_PLAYER_INVENTORY_ITEM_SLOT.Class;
}

void UPlayerInventoryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(460.0f, 700.0f);

	InitializeInventoryWnd();

	// 소지금 갱신
	UpdateSilver();

	for (auto itemSlot : ItemSlots)
	{
		auto info = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[itemSlot->GetItemSlotIndex()];

		//LOG(TEXT("[%d] itemcode = %s || isEmpty = %d"), 
		//	itemSlot->GetItemSlotIndex(),
		//	*info.ItemCode.ToString(), info.IsEmpty());
	}
}

void UPlayerInventoryWnd::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UPlayerInventoryWnd::InitializeInventoryWnd()
{
#pragma region Create Inventory Slots

	// 플레이어 캐릭터 정보를 얻습니다.
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	// 인벤토리 슬롯 개수를 얻습니다.
	int32 inventorySlotCount = playerInfo->InventorySlotCount;

	const int32 maxColumnCount = 6;
	int32 currentColumnCount = 0;

	// 인벤토리 슬롯들을 생성합니다.
	for (int32 i = 0; i < inventorySlotCount; ++i)
	{
		// 인벤토리 슬롯을 생성합니다.
		auto newItemSlot = CreateItemSlot();

		// 슬롯 초기화
		newItemSlot->InitializeItemSlot(
			ESlotType::ST_InventorySlot,
			playerInfo->InventoryItemInfos[i].ItemCode, i);

		// 생성한 슬롯을 정렬합니다.
		UWidgetControllerWidget::SortGridPanelElem(
			newItemSlot, maxColumnCount, currentColumnCount);
	}
#pragma endregion

#pragma region Lock Camera Zoom
	// 인벤토리 창이 열리면 카메라 줌을 막습니다.
	GetManager(UPlayerManager)->GetPlayerCharacter()->GetSpringArm()->SetUseZoom(false);

	// 인벤토리 창이 닫히면 카메라 줌을 사용할수 있도록 합니다.
	OnWndClosedEvent.AddLambda([this](UClosableWnd* closableWnd)
		{
			GetManager(UPlayerManager)->GetPlayerCharacter()->GetSpringArm()->SetUseZoom(true);
		});
#pragma endregion

}

UPlayerInventoryItemSlot* UPlayerInventoryWnd::CreateItemSlot()
{
	// 인벤토리 슬롯을 생성합니다.
	auto newItemSlot = CreateWidget<UPlayerInventoryItemSlot>(
		this, BP_PlayerInventoryItemSlot);

	ItemSlots.Add(newItemSlot);

	// GridPanel_ItemSlots 의 자식 위젯으로 추가합니다.
	GridPanel_ItemSlots->AddChild(newItemSlot);

	// 생성한 인벤토리 슬롯을 반환합니다.
	return newItemSlot;
}

void UPlayerInventoryWnd::UpdateInventoryItemSlots()
{
	FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	TArray<FItemSlotInfo>& inventoryIteminfos =
		playerInfo->InventoryItemInfos;

	for (int32 i = 0; i < ItemSlots.Num(); ++i)
	{
		auto itemSlot = ItemSlots[i];

		itemSlot->SetItemInfo(inventoryIteminfos[i].ItemCode);

		itemSlot->UpdateInventoryItemSlot();

		itemSlot->InitializeItemSlot(
			ESlotType::ST_InventorySlot,
			playerInfo->InventoryItemInfos[i].ItemCode, i);
	}
}

void UPlayerInventoryWnd::UpdateSilver()
{
	FText silverToText = FText::FromString(FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->Silver));
	Text_Silver->SetText(silverToText);
}
