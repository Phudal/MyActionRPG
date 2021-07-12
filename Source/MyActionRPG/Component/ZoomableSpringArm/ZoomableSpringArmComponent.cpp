// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"

UZoomableSpringArmComponent::UZoomableSpringArmComponent()
{
	// �⺻������ �� ����� ����ϵ��� ��
	bUseZoom = true;

	// �� �ּ�, �ִ� �Ÿ��� ����
	SetArmLengthMinMax(100.0f, 400.0f);
	
}

void UZoomableSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	// ��ǥ �Ÿ��� ����
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
	// �� ����� ������� �ʴ´ٸ� ī�޶� ���� �̷���� �� ������ ��
	if (!bUseZoom)
		return;

	ArmLengthTarget += (axis * -5.0f);
	ArmLengthTarget = FMath::Clamp(
		ArmLengthTarget, MinArmLength, MaxArmLength);
}
