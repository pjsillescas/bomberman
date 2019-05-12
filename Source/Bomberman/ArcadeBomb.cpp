// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeBomb.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"

#include "DamageComponent.h"
#include "BombermanCharacter.h"

void AArcadeBomb::Explode()
{
	UE_LOG(LogTemp, Warning, TEXT("Bomb destroyed!!"));

	//	BombMesh->SetVisibility(true);
	ExplosionParticle->Activate();

	for (auto Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Activating %s"), *(Component->GetName()));
		Component->Activate();
	}

	TArray<AActor*> OutActors;
	TArray<AActor*> ActorsToIgnore;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FVector Position = GetActorLocation();
	//UKismetSystemLibrary::SphereOverlapActors(this, Position, ExplosionRadius, ObjectTypes, nullptr, ActorsToIgnore, OutActors);

	TArray<FVector> Directions;

	Directions.Add(FVector::RightVector);
	Directions.Add(FVector::LeftVector);
	Directions.Add(FVector::ForwardVector);
	Directions.Add(FVector::BackwardVector);

	float Length = TILE_LENGTH * ScopeTiles;
	FVector Start = GetActorLocation();
	for (auto Direction : Directions)
	{
		FHitResult Hit;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		FCollisionResponseParams ResponseParams;
		FVector End = Start + Direction * Length;
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldDynamic, CollisionParams, ResponseParams))
		{
			if (Hit.bBlockingHit)
			{
				UE_LOG(LogTemp,Warning,TEXT("pozi"));
				AActor* ActorHit = Hit.Actor.Get();

				if (ActorHit)
				{
					UE_LOG(LogTemp, Warning, TEXT("Actor hit  %s yayyyy"), *(ActorHit->GetName()));
					UDamageComponent* DamageComponent = Cast<UDamageComponent>(ActorHit->GetComponentByClass(UDamageComponent::StaticClass()));

					if (DamageComponent != nullptr && ActorHit != this)
					{
						UE_LOG(LogTemp, Warning, TEXT("Actor with damage component"));

						float Damage = GetDamage(ActorHit);
						UE_LOG(LogTemp, Warning, TEXT("Actor %s bombed with a damage of %f!!"), *(ActorHit->GetName()), Damage);
						DamageComponent->ApplyDamage(Damage);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Actor %s has no damage component"), *(ActorHit->GetName()));
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Actor null"));
				}
			}
		}
	}

	if (BombermanOwner != nullptr)
	{
		BombermanOwner->AddBomb();
	}

}