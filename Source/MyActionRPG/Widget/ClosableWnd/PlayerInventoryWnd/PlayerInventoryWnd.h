// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "PlayerInventoryWnd.generated.h"


UCLASS()
class MYACTIONRPG_API UPlayerInventoryWnd : public UClosableWnd
{
	GENERATED_BODY()

private:
	TSubclassOf<class UPlayerInventoryItemSlot> BP_PlayerInventoryItemSlot;

private:
	TArray<class UPlayerInventoryItemSlot*> ItemSlots;

private:
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel_ItemSlots;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Silver;

public:
	UPlayerInventoryWnd(const FObjectInitializer& ObjectInitializer);

	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	
private:
	void InitializeInventoryWnd();

	// ������ ������ ����
	class UPlayerInventoryItemSlot* CreateItemSlot();

		
public:
	// �κ��丮 ������ ���Ե��� ������
	void UpdateInventoryItemSlots();

	// �������� ����
	void UpdateSilver();

public:
	TArray<class UPlayerInventoryItemSlot*>& GetItemSlots()
	{
		return ItemSlots;
	}
};
