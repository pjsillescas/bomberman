// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageComponent.h"

#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealthPoints = 30;
	HealthPoints = MaxHealthPoints;
	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthPoints = MaxHealthPoints;
	IsDead = false;
	// ...
	
}

void UDamageComponent::ApplyDamage(float Damage)
{
	HealthPoints -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Applying damage of %f resulting in health of %i"), Damage,HealthPoints);

	if (HealthPoints <= 0 && !IsDead)
	{
		IsDead = true;

		AActor* Owner = GetOwner();
		UE_LOG(LogTemp,Warning,TEXT("DamageComponent: Destroying Actor %s"),*(Owner->GetName()));

		if (OnDestroy.IsBound())
			OnDestroy.Execute();

		//GetOwner()->Destroy();
	}
}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

