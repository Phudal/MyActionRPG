// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Interface/ObjectPoolable.h"

#include "ObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API UObjectPool : public UObject
{
	GENERATED_BODY()
	
private:
	// 풀링할 객체들을 저장할 배열
	TArray<IObjectPoolable*> PoolObjects;

public:
	template<typename T>
	FORCEINLINE T* RegisterRecyclableObject(T* newRecyclableObject)
	{
		PoolObjects.Add(static_cast<IObjectPoolable*>(newRecyclableObject));
		return newRecyclableObject;
	}

	template<typename T>
	FORCEINLINE T* GetRecycledObject() const
	{
		return Cast<T>(GetRecycledObject());
	}

	// 재활용된 객체를 얻음
	IObjectPoolable* GetRecycledObject() const;

	// 특정한 조건식을 이용하여 재활용된 객체를 얻음
	template<typename Predicate>
	FORCEINLINE IObjectPoolable* GetRecycledObjectByPred(Predicate pred, bool checkUsing = true) const
	{
		for (auto poolableObject : PoolObjects)
		{
			if (pred(poolableObject) && (checkUsing ? poolableObject->GetCanRecyclable() : true))
				return poolableObject;
		}

		return nullptr;
	}

	// ID를 통해 재활용된 객체를 얻음
	FORCEINLINE IObjectPoolable* GetRecycledObjectByID(int32 id) const
	{
		return GetRecycledObjectByPred([this, id](IObjectPoolable* poolObj)
		{
			return poolObj->GetID() == id;
		});
	}
};
