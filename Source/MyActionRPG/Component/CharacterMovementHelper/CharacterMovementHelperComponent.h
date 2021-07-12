// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterMovementHelperComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONRPG_API UCharacterMovementHelperComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class APlayerCharacter* PlayerCharacter;

	float WalkSpeed;
	float RunSpeed;
	
public:	
	// Sets default values for this component's properties
	UCharacterMovementHelperComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool IsInAir() const;

public:
	void RunKeyPressed();
	void RunKeyReleased();

	void JumpKeyPressed();

	void InputHorizontal(float axis);
	void InputVertical(float axis);
};
