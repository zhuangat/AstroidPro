// Fill out your copyright notice in the Description page of Project Settings.


#include "RockBase.h"

#include "PlayerPawn.h"
#include "AstroidPro/AstroidProGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ARockBase::ARockBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static reference to the mesh to use for the base
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockMeshAsset(TEXT("StaticMesh'/Game/AstroidPro/Meshes/SM_Rock_A.SM_Rock_A'"));

	// Create mesh component for the projectile sphere
	RockMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	RockMeshComponent->SetStaticMesh(RockMeshAsset.Object);
	RockMeshComponent->SetupAttachment(RootComponent);
	RockMeshComponent->BodyInstance.SetCollisionProfileName("BlockAll"); // set up a notification for when this component hits something
	RockMeshComponent->OnComponentHit.AddDynamic(this, &ARockBase::OnHit);
	RootComponent = RockMeshComponent;
	
}

// Called when the game starts or when spawned
void ARockBase::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeTime);
	
	// random direction
	auto RandomDirection = FMath::RandPointInCircle(1);
	RandomDirection.Normalize();
	IntrinsicMoveDirection = { RandomDirection.X, RandomDirection.Y, 0.0f };

	// random Rotation
	const auto RandomRotationAxis = UKismetMathLibrary::RandomUnitVector();
	IntrinsicRotationAxis = RandomRotationAxis;
}

void ARockBase::Move(float DeltaTime)
{
	auto Movement = IntrinsicMoveDirection * MovementSpeed * DeltaTime;
	auto NewRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(IntrinsicRotationAxis, AngularSpeed * DeltaTime);
	NewRotation = RootComponent->GetComponentRotation() + NewRotation;
	FHitResult Hit;
	
	RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
	if (Hit.IsValidBlockingHit())
	{
		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
		RootComponent->MoveComponent(Deflection, NewRotation, true);
	}
}

// Called every frame
void ARockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void ARockBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	auto PlayerPawn = Cast<APlayerPawn>(OtherActor);
	if(PlayerPawn != nullptr)
	{
		PlayerPawn->GameOver();
	}
}

void ARockBase::OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit)
{
	auto AstroidGameMode = Cast<AAstroidProGameMode>(UGameplayStatics::GetGameMode(this));
	if (AstroidGameMode != nullptr)
	{
		AstroidGameMode->AddGameScore(Score);
	}
}

