// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Canhao.h"
#include "ProjectileActor.h"


// Sets default values
ACanhao::ACanhao()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(2.0f, 0.5f, 0.5f));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ACanhao::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerShoot, this, &ACanhao::Shoot,
		2.0f, true);
	
}

// Called every frame
void ACanhao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACanhao::Shoot() {
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		FVector Location = GetActorLocation();
		FRotator Rotation = MeshComp->GetComponentRotation();
		AProjectileActor* Proj = World->SpawnActor<AProjectileActor>(Location, Rotation,
			SpawnParameters);
		if (Proj) {
			Proj->SetIndex(0);
		}
	}
}