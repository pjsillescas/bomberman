// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = "Setup")
	float TimeToExplosion;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ExplosionRadius;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Setup")
	class UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float DamageBase;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	class UParticleSystemComponent* ExplosionParticle;

private:
	float SpawnTime;

	virtual void Explode();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual float GetDamage(class AActor* Actor);

	UPROPERTY(VisibleAnywhere,Category = "Setup")
	class UDamageComponent* DamageComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetExplosionRadius(float NewExplosionRadius);
	void SetTimeToExplosion(float NewTimeToExplosion);
};
