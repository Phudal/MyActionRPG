// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BaseSlot/ItemSlot/ItemSlot.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "Enum/PartsType.h"

#include "PlayerEquipSlot.generated.h"


UCLASS()
class MYACTIONRPG_API UPlayerEquipSlot : public UItemSlot
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_PartsName;
	
private:
	// 슬롯이 표시하는 파츠를 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPartsType PartsType;

	
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
public:
	void UpdateEquipSlot(FItemSlotInfo& itemSlotInfo);
	
	// 장비 아이템 장착 해제
	/// - inventorySlotIndex : 장착중읻너 장비 아이템을 어느 인벤토리 슬롯에 추가할 것인지를 지정함
	void DetachToEquipItemSlot(int32 inventorySlotIndex = INDEX_NONE);

public:
	FORCEINLINE EPartsType GetPartsType() const
	{
		return PartsType;
	}
};
