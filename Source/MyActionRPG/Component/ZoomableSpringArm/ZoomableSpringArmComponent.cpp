// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"

UZoomableSpringArmComponent::UZoomableSpringArmComponent()
{
	// 기본적으로 줌 기능을 사용하도록 함
	bUseZoom = true;

	// 줌 최소, 최대 거리를 설정
	SetArmLengthMinMax(100.0f, 400.0f);
	
}

void UZoomableSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	// 목표 거리를 설정
	TargetArmLength = ArmLengthTarget =
		(MaxArmLength - MinArmLength) * 0.5f;
}

void UZoomableSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SmoothZoomSpringArm(DeltaTime);
}

void UZoomableSpringArmComponent::SmoothZoomSpringArm(float dt)
{
	TargetArmLength = FMath::FInterpTo(
		TargetArmLength, ArmLengthTarget,
		dt, 5.0f);
}

void UZoomableSpringArmComponent::ZoomCamera(float axis)
{
	// 줌 기능을 사용하지 않는다면 카메라 줌이 이루어질 수 없도록 함
	if (!bUseZoom)
		return;

	ArmLengthTarget += (axis * -5.0f);
	ArmLengthTarget = FMath::Clamp(
		ArmLengthTarget, MinArmLength, MaxArmLength);
}
