// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolable.generated.h"


UINTERFACE(MinimalAPI)
class UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};


class MYACTIONRPG_API IObjectPoolable 
{
	GENERATED_BODY()

//public:
	// ��ü�� ������ ���� ���� ��� ����
	//virtual int32 GetID() const PURE_VIRTUAL(IObjectPoolable::GetID, return Not_us)
};
