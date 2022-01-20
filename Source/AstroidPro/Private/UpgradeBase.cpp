// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeBase.h"

// Sets default values
AUpgradeBase::AUpgradeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetCollisionProfileName("OverlapAll");
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AUpgradeBase::OnCollisionOverlap);
	RootComponent = CollisionComponent;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComponent->SetupAttachment(CollisionComponent);
	
}

// Called when the game starts or when spawned
void AUpgradeBase::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeTime);
}

// Called every frame
void AUpgradeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUpgradeBase::Upgrade(APlayerPawn* PlayerPawn)
{
	
}

void AUpgradeBase::OnCollisionOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerPawn = Cast<APlayerPawn>(OtherActor);
	if(PlayerPawn != nullptr)
	{
		Upgrade(PlayerPawn);
		Destroy();
	}
}

