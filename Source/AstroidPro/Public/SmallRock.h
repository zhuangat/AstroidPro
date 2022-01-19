// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RockBase.h"
#include "SmallRock.generated.h"

/**
 * 
 */
UCLASS()
class ASTROIDPRO_API ASmallRock : public ARockBase
{
	GENERATED_BODY()
	
	virtual void OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit) override;
};
