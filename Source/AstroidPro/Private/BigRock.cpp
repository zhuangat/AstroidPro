// Fill out your copyright notice in the Description page of Project Settings.


#include "BigRock.h"

void ABigRock::OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit)
{
	Super::OnProjectileInteract_Implementation(TargetProjectile, Hit);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// spawn two shards
	if (SplitRockClass != nullptr)
	{
		ARockBase* NewRock1 = GetWorld()->SpawnActor<ARockBase>(SplitRockClass, GetActorLocation(), FRotator::ZeroRotator, Params);
		ARockBase* NewRock2 = GetWorld()->SpawnActor<ARockBase>(SplitRockClass, GetActorLocation(), FRotator::ZeroRotator, Params);
	}
	
	Destroy();
}
