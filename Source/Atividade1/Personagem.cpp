// Fill out your copyright notice in the Description page of Project Settings.

#include "Atividade1.h"
#include "Personagem.h"
#include "ProjectileActor.h"


// Sets default values
APersonagem::APersonagem()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);
	}
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -80.0f));
	MeshComp->SetWorldScale3D(FVector(1.3f, 1.3f, 1.6f));
	MeshComp->SetupAttachment(GetCapsuleComponent());

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetWorldLocation(FVector(30.0f, 0.0f, 75.0f));
	ArrowComp->SetHiddenInGame(false);
	ArrowComp->ArrowSize = 2.0f;
	ArrowComp->SetCollisionProfileName("NoCollision");
	ArrowComp->SetupAttachment(MeshComp);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->SetWorldRotation(FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APersonagem::BeginPlay()
{
	Super::BeginPlay();
	
	Life = 3;
}

// Called every frame
void APersonagem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonagem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &APersonagem::Move);
	PlayerInputComponent->BindAxis("MoveSides", this, &APersonagem::MoveSides);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
		&APersonagem::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this,
		&APersonagem::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this,
		&APersonagem::StopRun);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this,
		&APersonagem::Shoot);


}

void APersonagem::Move(float Value) {
	FVector Direction(1.0f, 0.0f, 0.0f);
	if (Value > 0.0f) {
		MeshComp->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	} else if (Value < 0.0f) {
		MeshComp->SetWorldRotation(FRotator(0.0f, -180.0f, 0.0f));
	}
	AddMovementInput(Direction, Value);
}

void APersonagem::MoveSides(float Value) {
	FVector Direction(0.0f, 1.0f, 0.0f);
	if (Value > 0.0f) {
		MeshComp->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	} else if (Value < 0.0f) {
		MeshComp->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	AddMovementInput(Direction, Value);
}

void APersonagem::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void APersonagem::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void APersonagem::SetLife(int32 NewLife) {
	Life = NewLife;
}

int32 APersonagem::GetLife() {
	return Life;
}

void APersonagem::Shoot() {
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		FVector Location = ArrowComp->GetComponentLocation();
		FRotator Rotation = MeshComp->GetComponentRotation();
		AProjectileActor* Proj = World->SpawnActor<AProjectileActor>(Location, Rotation,
			SpawnParameters);
		if (Proj != nullptr) {
			Proj->SetIndex(1);
		}
	}
}

void APersonagem::SetCollected(int32 NewCollected) {
	Collected = NewCollected;
}

int32 APersonagem::GetCollected() {
	return Collected;
}

void APersonagem::AddCollected() {
	Collected++;
}

void APersonagem::SetInside(bool NewInside) {
	Inside = NewInside;
}

bool APersonagem::IsInside() {
	return Inside;
}