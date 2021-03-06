// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "AstroidPro/AstroidProGameMode.h"
#include "AstroidPro/AstroidProProjectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

const FName APlayerPawn::MoveForwardBinding("MoveForward");
const FName APlayerPawn::MoveRightBinding("MoveRight");
const FName APlayerPawn::FireBinding("Fire");

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
	bIsAlive = true;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	// If non-zero size, move this actor
	if (bIsAlive && Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	// We assume that the ship only fires to his forward vector
	const FVector FireDirection = GetActorForwardVector();

	// Try and fire a shot
	FireShot(FireDirection);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction(FireBinding, IE_Pressed, this, &APlayerPawn::OnFirePressed);
	PlayerInputComponent->BindAction(FireBinding, IE_Released, this, &APlayerPawn::OnFireReleased);
}

void APlayerPawn::FireShot(FVector FireDirection)
{
	
	// If it's ok to fire again
	if (bIsAlive && bCanFire == true)
	{
		// If we are pressing fire button
		if (bIsFireInputPressed == true)
		{
			const uint8 Ammo = FireUpgradeLevel * 2 + 1;
			for (uint8 Index = 0; Index < Ammo; Index++)
			{
				FRotator FanOffset;
				if (Index % 2 == 0 )
				{
					FanOffset = FRotator(0.0f, Index / 2 * FireFanWidth, 0.0f);
				}
				else
				{
					FanOffset = FRotator(0.0f, - (Index + 1 / 2) * FireFanWidth, 0.0f);
				}
				const FRotator FireRotation = FireDirection.Rotation() + FanOffset;
				// Spawn projectile at an offset from this pawn
				const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

				UWorld* const World = GetWorld();
				if (World != nullptr)
				{
					// spawn the projectile
					World->SpawnActor<AAstroidProProjectile>(SpawnLocation, FireRotation);
				}
			}
			
			bCanFire = false;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &APlayerPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void APlayerPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void APlayerPawn::OnFirePressed()
{
	bIsFireInputPressed = true;
}

void APlayerPawn::OnFireReleased()
{
	bIsFireInputPressed = false;
}

void APlayerPawn::UpgradeFire()
{
	FireUpgradeLevel += 1;
	FireUpgradeLevel = FMath::Clamp(FireUpgradeLevel, static_cast<uint8>(0), MaxUpgrade);
}

void APlayerPawn::GameOver()
{
	bIsAlive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	auto AstroidProGameMode = Cast<AAstroidProGameMode>(GetWorld()->GetAuthGameMode());
	if(AstroidProGameMode != nullptr)
	{
		AstroidProGameMode->DoGameOver();
	}
		
}

