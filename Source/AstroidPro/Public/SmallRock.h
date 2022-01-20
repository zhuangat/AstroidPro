// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RockBase.h"
#include "UpgradeBase.h"
#include "SmallRock.generated.h"

/**
 * 
 */
UCLASS()
class ASTROIDPRO_API ASmallRock : public ARockBase
{
	GENERATED_BODY()

	UPROPERTY(Category = Gameplay, EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<AUpgradeBase> RewardUpgradeClass;

	UPROPERTY(Category = Gameplay, EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float DropRate = 0.15f;
	
	virtual void OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit) override;
};
