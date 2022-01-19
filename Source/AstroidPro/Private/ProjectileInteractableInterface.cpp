// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileInteractableInterface.h"

#include "AstroidPro/AstroidPro.h"


// Add default functionality here for any IProjectileInteractableInterface functions that are not pure virtual.
void IProjectileInteractableInterface::OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile,
	const FHitResult& Hit)
{
	UE_LOG(LogAstroidPro, Display, TEXT("DEFAULT: hit by projectile %s."), *TargetProjectile->GetName());
}
