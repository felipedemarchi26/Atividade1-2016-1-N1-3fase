// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Enemy.h"
#include "Personagem.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
 	MeshComp->bGenerateOverlapEvents = true;
	MeshComp->SetCollisionProfileName("OverlapAllDynamic");
	MeshComp->OnComponentBeginOverlap.AddDynamic(this,
		&AEnemy::OnOverlapBegin);
	MeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 2.25f));
	RootComponent = MeshComp;

	Multiply = 1.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActualLocation = GetActorLocation();
	ActualLocation.Y += (1.0f*Multiply);
	SetActorLocation(ActualLocation);
	if (ActualLocation.Y >= InitialLocation.Y + 700.0f || 
		ActualLocation.Y <= InitialLocation.Y) {
		Multiply *= -1.0f;
	}

}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor != nullptr &&
		OtherActor->IsA(APersonagem::StaticClass())) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->SetLife(Personagem->GetLife() - 1);
		UE_LOG(LogTemp, Warning, TEXT("Hit! Life: %d"), 
			Personagem->GetLife());

	}

}

