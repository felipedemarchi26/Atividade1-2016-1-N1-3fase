// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Coletavel.h"
#include "Personagem.h"


// Sets default values
AColetavel::AColetavel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>
		(TEXT("CollisionComp"));

	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, 
		&AColetavel::OnOverlapBegin);

	CollisionComp->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -10.0f));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AColetavel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColetavel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColetavel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr &&
		OtherActor->IsA(APersonagem::StaticClass())) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->AddCollected();
		UE_LOG(LogTemp, Warning, TEXT("Collected: %d"), 
			Personagem->GetCollected());
		Destroy();

	}
}
