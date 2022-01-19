// Fill out your copyright notice in the Description page of Project Settings.


#include "RockSpawnerComponent.h"
#include "RockBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
URockSpawnerComponent::URockSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initial Variables
	SpawningRadius = 1000.0f;
	SpawningRate = 1.0f;
	bCanSpawn = true;
}


// Called when the game starts
void URockSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URockSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	SpawnRocks();
}

void URockSpawnerComponent::SpawnRocks()
{
	if(bCanSpawn == false || RockTypes.Num() == 0)
	{
		return;
	}
	
	const int32 NumToSpawn = FMath::RandRange(1, MaxSpawnInOneShot);
	for (int32 Idx = 0; Idx < NumToSpawn; Idx++)
	{
		const int32 RandomClassIndex = FMath::RandRange(0, RockTypes.Num() - 1);
		TSubclassOf<ARockBase> RandomClass = RockTypes[RandomClassIndex];
		auto RandomDirection= FMath::RandPointInCircle(1);
		RandomDirection.Normalize();
		FVector SpawnPosition = GetComponentLocation() + FVector(RandomDirection, 0.0f) * SpawningRadius;

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		auto NewRock = GetWorld()->SpawnActor<ARockBase>(RandomClass, SpawnPosition, FRotator::ZeroRotator, Params);
	}

	bCanSpawn = false;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetSpawn, this, &URockSpawnerComponent::ResetSpawn, SpawningRate);
}

void URockSpawnerComponent::ResetSpawn()
{
	bCanSpawn = true;
}

