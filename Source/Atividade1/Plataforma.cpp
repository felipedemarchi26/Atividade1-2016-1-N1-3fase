// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Plataforma.h"


// Sets default values
APlataforma::APlataforma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*CollisionComp = CreateDefaultSubobject<UBoxComponent>
		(TEXT("CollisionComp"));
	CollisionComp->SetCollisionProfileName("BlockAllDynamic");
	CollisionComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RootComponent = CollisionComp;*/

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	RootComponent = MeshComp;

	Multiply = 1.0f;
}

// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Na vertical
	if (Direction == 1) {
		FVector ActualLocation = GetActorLocation();
		ActualLocation.Z += (1.0f*Multiply);
		SetActorLocation(ActualLocation);
		if (ActualLocation.Z >= InitialLocation.Z + 400.0f) {
			Multiply *= -1.0f;
		} else if (ActualLocation.Z <= InitialLocation.Z) {
			Multiply *= -1.0f;
		}
	} else if (Direction == 2) {
		//Na horizontal
		FVector ActualLocation = GetActorLocation();
		ActualLocation.X += (1.0f*Multiply);
		SetActorLocation(ActualLocation);
		if (ActualLocation.X >= InitialLocation.X + 600.0f) {
			Multiply *= -1.0f;
		} else if (ActualLocation.X <= InitialLocation.X) {
			Multiply *= -1.0f;
		}
	}

}

