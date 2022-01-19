// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallRock.h"

void ASmallRock::OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit)
{
	Super::OnProjectileInteract_Implementation(TargetProjectile, Hit);

	Destroy();
}
