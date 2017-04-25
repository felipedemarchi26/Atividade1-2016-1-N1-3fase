// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "ProjectileActor.h"
#include "Personagem.h"
#include "Enemy.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>
		(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,
		&AProjectileActor::OnOverlapBegin);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -10.0f));
	MeshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	MeshComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->UpdatedComponent = RootComponent;

	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	Index = 0;
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr
		&& OtherActor->IsA(APersonagem::StaticClass())
		&& Index != 1) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->SetLife(Personagem->GetLife() - 1);
		UE_LOG(LogTemp, Warning, TEXT("Life: %d"), Personagem->GetLife());
		Destroy();
	} else if (OtherActor != nullptr &&
		OtherActor->IsA(AEnemy::StaticClass()) &&
		Index == 1) {

		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Enemy Destroyed"));
		Destroy();

	}
	
}

void AProjectileActor::SetIndex(int8 NewIndex) {
	Index = NewIndex;
}

int8 AProjectileActor::GetIndex() {
	return Index;
}