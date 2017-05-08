// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Boss.h"
#include "ProjectileBoss.h"


// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerDrop, this, &ABoss::TimeToDrop,
		3.0f, true);
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActualLocation = GetActorLocation();
	if (Control == 0) {
		ActualLocation.Y += 5.0f;
		if (ActualLocation.Y >= 0) {
			Control++;
		}
	} else if (Control == 1) {
		ActualLocation.X += 5.0f;
		if (ActualLocation.X >= 3500.0f) {
			Control++;
		}
	} else if (Control == 2) {
		ActualLocation.Y += 5.0f;
		if (ActualLocation.Y >= 750.0f) {
			Control++;
		}
	} else if (Control == 3) {
		ActualLocation.X += 5.0f;
		if (ActualLocation.X >= 4000.0f) {
			Control++;
		}
	} else if (Control == 4) {
		ActualLocation.Y -= 5.0f;
		if (ActualLocation.Y <= -980.0f) {
			Control++;
		}
	} else if (Control == 5) {
		ActualLocation.X -= 5.0f;
		if (ActualLocation.X <= 3150.0f) {
			Control = 0;
		}
	}
	SetActorLocation(ActualLocation);

}

void ABoss::TimeToDrop() {
	UE_LOG(LogTemp, Warning, TEXT("Drop"));
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		FVector Location = GetActorLocation();
		World->SpawnActor<AProjectileBoss>(Location,
			FRotator::ZeroRotator, SpawnParameters);
	}
}