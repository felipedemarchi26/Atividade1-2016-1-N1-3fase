// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class ATIVIDADE1_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetIndex(int8 NewIndex);
	int8 GetIndex();

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
		USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Properties")
		int8 Index;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
