// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "Enum/PartsType.h"

#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API APlayerCharacter final : public ABaseCharacter
{
	GENERATED_BODY()

private:
	TSubclassOf<class UPlayerCharacterAnimInst> BP_PlayerCharacterAnimInst;

private:
	UPROPERTY()
	TMap<EPartsType, class USkeletalMeshComponent*> Parts;

private:
#pragma region Custom Components
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCharacterMovementHelperComponent* CharacterMovementHelper;
	
	
#pragma endregion

#pragma region SkeletalMeshComponents
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* HeadMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* HairMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BeardMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* TopMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BottomMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* RGloveMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* LGloveMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ShoesMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;
	
#pragma endregion 

public:
	APlayerCharacter();

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	void InitializeMeshs();

	// TODO
	// Component Getter

	FORCEINLINE class UCharacterMovementHelperComponent* GetCharacterMovementHelper() const
	{
		return CharacterMovementHelper;
	}

	FORCEINLINE TMap<EPartsType, class USkeletalMeshComponent*>& GetParts()
	{
		return Parts;
	}
	

private:
	void RegularAttack();
};
