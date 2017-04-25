// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

UCLASS()
class ATIVIDADE1_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//UPROPERTY(EditAnywhere, Category = "Collision")
	//	UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* MeshComp;

	/*
	0 - Estático
	1 - De cima para baixo
	2 - Da direita para esquerda
	*/
	UPROPERTY(EditAnywhere, Category = "Properties")
		int8 Direction; 

	UPROPERTY(EditAnywhere, Category = "Properties")
		FVector InitialLocation;

	UPROPERTY(EditAnywhere, Category = "Properties")
		float Multiply;

	
	
};
