// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Item.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->bGenerateOverlapEvents = true;
	MeshComp->SetCollisionProfileName("OverlapAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

