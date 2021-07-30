// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

FItemSlotInfo::FItemSlotInfo()
	: FItemSlotInfo(TEXT(""))
{
	
}

FItemSlotInfo::FItemSlotInfo(FName itemCode, int32 itemCount, int32 maxSlotCount)
{
	ItemCode = itemCode;
	ItemCount = itemCount;
	MaxSlotCount = maxSlotCount;
}
