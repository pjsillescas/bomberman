// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"

#include "DamageComponent.h"
#include "BombermanCharacter.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeToExplosion = 5;
	ExplosionRadius = 40;
	DamageBase = 20;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BombMesh"));
	SetRootComponent(BombMesh);

	DamageComponent = CreateDefaultSubobject<UDamageComponent>(FName("DamageComponent"));
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("ExplosionParticle"));
	//ExplosionParticle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionParticle->bAutoActivate = true;
	ExplosionParticle->SetActive(true);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	SpawnTime = GetWorld()->GetTimeSeconds();
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetTimeSeconds() - SpawnTime > TimeToExplosion)
	{
		Destroy();
	}
}

void ABomb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Explode();
	
	Super::EndPlay(EndPlayReason);
}

void ABomb::Explode()
{
	UE_LOG(LogTemp,Warning,TEXT("Bomb destroyed!!"));
	
//	BombMesh->SetVisibility(true);
	ExplosionParticle->Activate();

	for (auto Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Activating %s"),*(Component->GetName()));
		Component->Activate();
	}

	TArray<AActor*> OutActors;
	TArray<AActor*> ActorsToIgnore;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FVector Position = GetActorLocation();
	UKismetSystemLibrary::SphereOverlapActors(this, Position, ExplosionRadius, ObjectTypes, nullptr, ActorsToIgnore, OutActors);

	for (auto Actor : OutActors)
	{
		UDamageComponent* DamageComponent = Cast<UDamageComponent>(Actor->GetComponentByClass(UDamageComponent::StaticClass()));

		if (DamageComponent != nullptr && Actor != this)
		{
			float Damage = GetDamage(Actor);
			UE_LOG(LogTemp, Warning, TEXT("Actor %s bombed with a damage of %f!!"), *(Actor->GetName()),Damage);
			DamageComponent->ApplyDamage(Damage);
		}
	}

	if (BombermanOwner != nullptr)
	{
		BombermanOwner->AddBomb();
	}
}

float ABomb::GetDamage(AActor* Actor)
{
	if (GetOwner() == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Owner is null"));
		return DamageBase;
	}

	if (Actor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is null"));
		return DamageBase;
	}

	FVector Distance = GetOwner()->GetActorLocation() - Actor->GetActorLocation();
	float DistanceLength = Distance.Size();

	float Damage = (ExplosionRadius > 0) ? DamageBase * FMath::Clamp<float>(1 - DistanceLength / ExplosionRadius,0,1) : 0;

	return Damage;
}


void ABomb::SetExplosionRadius(float NewExplosionRadius)
{
	ExplosionRadius = NewExplosionRadius;
}

void ABomb::SetTimeToExplosion(float NewTimeToExplosion)
{
	TimeToExplosion = NewTimeToExplosion;
}

void ABomb::SetBombermanOwner(class ABombermanCharacter* NewBombermanOwner)
{
	BombermanOwner = NewBombermanOwner;
}
