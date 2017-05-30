// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "ProjectileBoss.h"
#include "Personagem.h"


// Sets default values
AProjectileBoss::AProjectileBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>
		(TEXT("CollisionComp"));
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,
		&AProjectileBoss::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this,
		&AProjectileBoss::OnOverlapEnd);
	CollisionComp->SetSphereRadius(150.0f);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh
	(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetupAttachment(CollisionComp);

	//Criou o componente referente ao sistema de partícula
	Particle = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("ParticleSystem"));
	//Desabilita a auto ativação da partículo ao criar
	Particle->bAutoActivate = false;
	//Carrega a partícula a ser utilizada
	ConstructorHelpers::FObjectFinder<UParticleSystem> LoadParticle
	(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	//Verifica se conseguiu carregar com sucesso
	if (LoadParticle.Succeeded()) {
		//Define o templete do componente referente a partícula
		//como a partícula carregada.
		Particle->SetTemplate(LoadParticle.Object);
	}
	//Anexa a partícula ao Root Component
	Particle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectileBoss::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerExplosion, this,
		&AProjectileBoss::TimeToExplode, 2.0f, false);

}

// Called every frame
void AProjectileBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBoss::TimeToExplode() {
	UE_LOG(LogTemp, Warning, TEXT("Explode!"));
	GetWorldTimerManager().ClearTimer(TimerExplosion);
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Pawn != nullptr) {
		APersonagem* Personagem = Cast<APersonagem>(Pawn);
		if (Personagem != nullptr && Personagem->IsInside()) {
			Personagem->SetActorLocation(FVector(-650.0f, 30.0f, 108.0f));
		}
	}
	//Destroy();
	Particle->ToggleActive();
	MeshComp->SetVisibility(false);
	GetWorldTimerManager().SetTimer(TimerDestroy, this,
		&AProjectileBoss::TimeToDestroy, 1.0f, false);
}

void AProjectileBoss::TimeToDestroy() {
	GetWorldTimerManager().ClearTimer(TimerDestroy);
	Destroy();
}

void AProjectileBoss::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && 
		OtherActor->IsA(APersonagem::StaticClass())) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->SetInside(true);
		UE_LOG(LogTemp, Warning, TEXT("Inside"));

	}
}

void AProjectileBoss::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor != nullptr &&
		OtherActor->IsA(APersonagem::StaticClass())) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->SetInside(false);
		UE_LOG(LogTemp, Warning, TEXT("Outside"));

	}
}