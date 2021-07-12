// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZoomableSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API UZoomableSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

private:
	bool bUseZoom;

	float ArmLengthTarget;
	float MinArmLength;
	float MaxArmLength;

public:
	UZoomableSpringArmComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 부드럽게 줌이 이루어질 수 있도록 함
	void SmoothZoomSpringArm(float dt);

public:
	// 카메라 줌을 수행함
	/// - APlayerCharacter 에서 마우스 휠 입력에 바인딩
	void ZoomCamera(float axis);

public:
	FORCEINLINE void SetUseZoom(bool bUse)
	{
		bUseZoom = bUse;
	}

	FORCEINLINE void SetArmLengthMinMax(float min, float max)
	{
		MinArmLength = min;
		MaxArmLength = max;
	}
};
