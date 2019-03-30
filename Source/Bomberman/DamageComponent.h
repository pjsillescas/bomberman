// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnDestroy);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = "Setup")
	int32 MaxHealthPoints;

	int32 HealthPoints;

	FOnDestroy OnDestroy;
	bool IsDead;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void ApplyDamage(float Damage);

	UFUNCTION(BlueprintCallable,Category = "Setup")
	int32 GetHealthPoints() const { return HealthPoints; }

	UFUNCTION(BlueprintCallable,Category = "Setup")
	void SetOnDestroy(const FOnDestroy& NewOnDestroy) { OnDestroy = NewOnDestroy; }

};
