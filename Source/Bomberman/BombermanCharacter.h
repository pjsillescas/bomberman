// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombermanCharacter.generated.h"

UCLASS(config=Game)
class ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

	const int32 DEFAULT_MAXBOMBS = 1;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ABombermanCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Status")
	bool IsDead() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 DefaultMaxBombs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 MaxBombs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 CurrentBombs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	class UDamageComponent* DamageComponent;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void AddBomb();

	UFUNCTION(BlueprintCallable,Category = "Status")
	void IncreaseMaxBombs();

protected:
	void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void PlaceBomb();

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<class ABomb> BombClass;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

