// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Boss.generated.h"

UCLASS()
class ATIVIDADE1_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		int Control;

	FTimerHandle TimerDrop;

	void TimeToDrop();
	
};
