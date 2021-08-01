// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BaseSlot/ItemSlot/ItemSlot.h"

#include "Single/GameInstance/RPGGameInst.h"

#include "Components/Image.h"

UItemSlot::UItemSlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ItemInfo.DT_ItemInfo'"));

	if (DT_ITEM_INFO.Succeeded())
		DT_ItemInfo = DT_ITEM_INFO.Object;
}

void UItemSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	Super::InitializeSlot(slotType, inCode);

	// 아이템 정보 설정
	SetItemInfo(inCode);

	// 아이템 이미지 설정
	UpdateItemImage();	
}

void UItemSlot::UpdateItemImage()
{
	UTexture2D* itemImage = nullptr;

	// 아이템 정보가 비어있다면 투명한 이미지를 사용
	if (ItemInfo.IsEmpty())
		itemImage = T_Null;
	
	// 아이템 정보가 비어있지 않은 경우
	else
	{
		// 아이템 이미지 경로가 비어있다면 투명한 이미지 사용
		if (ItemInfo.ItemImagePath.IsNull())
			itemImage = T_Null;

		// 아이템 이미지 경로가 비어있지 않다면 아이템 이미지를 로드하여 사용
		else
			itemImage = Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(ItemInfo.ItemImagePath));
	}

	// 아이템 이미지 사용
	GetSlotImage()->SetBrushFromTexture(itemImage);	
}

void UItemSlot::SetItemInfo(FName itemCode)
{
	// 아이템 코드가 비어있다면
	if (itemCode.IsNone())
	{
		// 아이템 정보를 비움
		ItemInfo = FItemInfo();
		return;
	}

	// 아이템 정보 찾기
	FString contextString;
	FItemInfo* findedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);	

	// 아이템 정보를 찾지 못했다면 아이템 정보를 비움
	if (findedItemInfo == nullptr)
		ItemInfo = FItemInfo();

	else
		ItemInfo = *findedItemInfo;
}
