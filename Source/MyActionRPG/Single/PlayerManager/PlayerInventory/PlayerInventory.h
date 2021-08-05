// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Struct/ItemSlotInfo/ItemSlotInfo.h"
#include "UObject/NoExportTypes.h"

#include "Enum/InputModeType.h"
#include "Enum/PartsType.h"

#include "PlayerInventory.generated.h"

#ifndef ITEM_ALL
#define ITEM_ALL -1
#endif


UCLASS()
class MYACTIONRPG_API UPlayerInventory : public UObject
{
	GENERATED_BODY()

private:
	TSubclassOf<class UPlayerInventoryWnd> BP_PlayerInventoryWnd;

	TSubclassOf<class UPlayerEquipItemWnd> BP_EquipItemWnd;

	class UDataTable* DT_EquipItemInfo;

private:
	UPROPERTY()
	class UPlayerInventoryWnd* PlayerInventoryWnd;

	UPROPERTY()
	class UPlayerEquipItemWnd* PlayerEquipItemWnd;

public:
	UPlayerInventory();	

	
public:
	// �κ��丮 â�� ������
	class UPlayerInventoryWnd* CreateInventoryWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, 
		bool bShowCursor = true);

	// ��� ������ â�� ������
	class UPlayerEquipItemWnd* CreateEquipItemWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default,
		bool bShowCursor = true);

	// �κ��丮 â�� ����
	void CloseInventoryWnd();

	// ��� ������ â�� ����
	void CloseEquipItemWnd();

	// �κ��丮 â�� �����
	void ToggleInventoryWnd(class UWidgetControllerWidget* widgetController, bool bOpenEquipItemWnd = false);

	// ��� â�� �����
	void ToggleEquipItemWnd(class UWidgetControllerWidget* widgetController);
	
	// ������ ���� ������ ����
	FItemSlotInfo* GetItemSlotInfo(int32 slotIndex) const;
	
	// �κ��丮 ������ ��ü
	void SwapItem(class UPlayerInventoryItemSlot* first, class UPlayerInventoryItemSlot* second);

	// �������� �κ��丮�� �߰���
	bool AddItem(FItemSlotInfo& newItemSlotInfo);
	
	// ������ �������� ��ħ
	void MergeItem(class UPlayerInventoryItemSlot* ori, class UPlayerInventoryItemSlot* target);

	// �������� �κ��丮���� ������
	/// - itemSlotIndex : ������ ���� �ε����� ������
	/// - removeCoutn : ������ ����
	///   ITEM_ALL�� ���޵ȴٸ� ��� �������� ����
	void RemoveItem(int32 itemSlotIndex, int32 removeCount = ITEM_ALL);

	// ��� �������� ������
	/// - equipItemCode : �����Ϸ��� ������ �ڵ带 ������
	/// - out_PrevItemSlotInfo: ������ ������ ������ ������ ���� ItemSlotInfo ������ ����
	void EquipItem(FName equipItemCode, FItemSlotInfo* out_PrevItemSlotInfo = nullptr);
	

	// ��� �������� ���� ������
	/// - partsType : ���� �����Ϸ��� ������ ������
	/// - out_ItemSlotInfo : ������ ������ ������ ������ ���� ItemSlotInfo ������ ������
	void DismountItem(EPartsType partsType, FItemSlotInfo* out_ItemSlotInfo = nullptr);

	// �÷��̾� ĳ������ ������� ������
	/// - ��� Mesh�� ���ŵ�
	void UpdateCharacterVisual();

	// �÷��̾� ĳ���� ������� ������
	/// - updateParts : ���Ž�ų ������ ������
	/// - equipItemInfo : ��� ������ ������ ������
	///   - ���� nullptr �� �����Ѵٸ� �� �޼��� ������ ĳ���Ϳ� ������ ��� ������ �̿��Ͽ� �����͸� ����
	void UpdateCharacterVisual(EPartsType updateParts, struct FEquipItemInfo* equipItemInfo = nullptr);
	
public:
	FORCEINLINE class UPlayerInventoryWnd* GetPlayerInventoryWnd() const
	{
		return PlayerInventoryWnd;
	}

	FORCEINLINE class UPlayerEquipItemWnd* GetPlayerEquipItemWnd() const
	{
		return PlayerEquipItemWnd;
	}
};
