// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AstroidPro/AstroidProProjectile.h"
#include "UObject/Interface.h"
#include "ProjectileInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UProjectileInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ASTROIDPRO_API IProjectileInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnProjectileInteract(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit);

	virtual void OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit);
};
