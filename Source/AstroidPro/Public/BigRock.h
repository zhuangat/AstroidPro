// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RockBase.h"
#include "BigRock.generated.h"

/**
 * 
 */
UCLASS()
class ASTROIDPRO_API ABigRock : public ARockBase
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true));
	TSubclassOf<ARockBase> SplitRockClass;
	
	public:
	
	virtual void OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit) override;
};
