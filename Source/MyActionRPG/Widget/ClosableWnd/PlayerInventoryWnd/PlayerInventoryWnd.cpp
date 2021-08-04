// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ClosableWnd/PlayerInventoryWnd/PlayerInventoryWnd.h"

#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/RPGGameInst.h"

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
	static ConstructorHelpers::FClassFinder<UPlayerInventoryItemSlot> BP_PLAYER_INVENTORY_SLOT(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Slot/BP_PlayerInventoryItemSlot.BP_PlayerInventoryItemSlot_C'"));

	if (BP_PLAYER_INVENTORY_SLOT.Succeeded())
		BP_PlayerInventoryItemSlot = BP_PLAYER_INVENTORY_SLOT.Class;
}

void UPlayerInventoryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(460.0f, 700.0f);

	InitializeInventoryWnd();

	// ������ ����
	UpdateSilver();

	for (auto itemSlot : ItemSlots)
	{
		auto info = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[itemSlot->GetItemSlotIndex()];
	}
}

void UPlayerInventoryWnd::InitializeInventoryWnd()
{
#pragma region Create Inventory Slots

	// �÷��̾� ĳ���� ������ ����
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	// �κ��丮 ���� ������ ����
	int32 inventorySlotCount = playerInfo->InventorySlotCount;

	const int32 maxColumCount = 6;
	int32 currentColumnCount = 0;

	// �κ��丮 ���Ե��� ������
	for (int32 i = 0; i < inventorySlotCount; i++)
	{
		// �κ��丮 ���� ����
		auto newItemSlot = CreateItemSlot();

		// ���� �ʱ�ȭ
		newItemSlot->InitializeItemSlot(
			ESlotType::ST_InventorySlot,
			playerInfo->InventoryItemInfos[i].ItemCode, i);

		// ������ ������ ������
		UWidgetControllerWidget::SortGridPanelElem(newItemSlot, maxColumCount, currentColumnCount);
	}
#pragma endregion

#pragma region Lock Camera Zoom
	// �κ��丮 â�� ������ ī�޶� ���� ����
	GetManager(UPlayerManager)->GetPlayerCharacter()->GetSpringArm()->SetUseZoom(false);

	// �κ��丮 â�� ������ ī�޶� ���� ����� �� �ֵ��� ��
	OnWndClosedEvent.AddLambda([this](UClosableWnd* ClosableWnd)
		{
			GetManager(UPlayerManager)->GetPlayerCharacter()->GetSpringArm()->SetUseZoom(true);
		});
#pragma endregion 
}

UPlayerInventoryItemSlot* UPlayerInventoryWnd::CreateItemSlot()
{
	// �κ��丮 ������ ������
	auto newItemSlot = CreateWidget<UPlayerInventoryItemSlot>(this, BP_PlayerInventoryItemSlot);

	ItemSlots.Add(newItemSlot);

	// GridPanel_ItemSlots �� �ڽ� �������� �߰���
	GridPanel_ItemSlots->AddChild(newItemSlot);

	// ������ �κ��丮 ������ ��ȯ��
	return newItemSlot;
}

void UPlayerInventoryWnd::UpdateSilver()
{
	FPlayerCharacterInfo* PlayerCharacterInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	TArray<FItemSlotInfo>& inventoryItemInfos = PlayerCharacterInfo->InventoryItemInfos;

	for (int32 i = 0; i < ItemSlots.Num(); i++)
	{
		auto itemSlot = ItemSlots[i];

		itemSlot->SetItemInfo(inventoryItemInfos[i].ItemCode);

		itemSlot->UpdateInventoryItemSlot();

		itemSlot->InitializeItemSlot(ESlotType::ST_InventorySlot, 
			PlayerCharacterInfo->InventoryItemInfos[i].ItemCode, i);
	}
}

void UPlayerInventoryWnd::UpdateInventoryItemSlots()
{
	FText silverToText = FText::FromString(FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->Silver));
	Text_Silver->SetText(silverToText);
}
