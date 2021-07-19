// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolable.generated.h"

#ifndef OBJECT_POOLABLE_ID
#define OBJECT_POOLABLE_ID
#define NOT_USE_INSTANCE_ID -1
#endif

#ifndef IMPLEMENT_OBJECT_POOLABLE
#define IMPLEMENT_OBJECT_POOLABLE \
private: \
	int32 poolableObjID; \
	bool bCanRecyclable; \
public: \
	FORCEINLINE virtual int32 GetID() const override { return poolableObjID; } \
	FORCEINLINE virtual bool GetCanRecyclable() const override { return bCanRecyclable; } \
	FORCEINLINE virtual void SetCanRecyclable(bool canRecyclable) override { bCanRecyclable = canRecyclable; }

#define INITIALIZE_OBJECT_POOLABLE(id) poolableObjID = id; bCanRecyclable = false;

#define DEF_SETID \
public: \
	FORCEINLINE void SetID(int32 newId) { poolableObjID = newId; }

#endif


UINTERFACE(MinimalAPI)
class UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};


class MYACTIONRPG_API IObjectPoolable
{
	GENERATED_BODY()

public:
	// ��ü�� ������ ���� ���� ��� ����
	virtual int32 GetID() const PURE_VIRTUAL(IObjectPoolable::GetID, return NOT_USE_INSTANCE_ID;);

	// ���� ���� ���θ� ��Ÿ���� ������ ���� ������ / ������
	virtual bool GetCanRecyclable() const PURE_VIRTUAL(IObjectPoolable::GetCanRecyclable, return true;);
	virtual void SetCanRecyclable(bool canRecyclable) PURE_VIRTUAL(IObjectPoolable::SetCanRecyclable, );

	// ��ü�� ����� �� ȣ��Ǵ� �޼���
	virtual void OnRecycleStart() PURE_VIRTUAL(IObjectPoolable::OnRecycleStart, );
};
