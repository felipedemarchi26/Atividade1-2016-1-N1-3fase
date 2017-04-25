// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Personagem.generated.h"

UCLASS()
class ATIVIDADE1_API APersonagem : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetLife(int32 NewLife);
	int32 GetLife();
	void SetCollected(int32 NewCollected);
	int32 GetCollected();
	void AddCollected();

private:

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Arrow")
		UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Life")
		int32 Life;

	UPROPERTY(EditAnywhere, Category = "Properties")
		int32 Collected;

	void Move(float Value);
	void MoveSides(float Value);
	void StartRun();
	void StopRun();
	void Shoot();
};
