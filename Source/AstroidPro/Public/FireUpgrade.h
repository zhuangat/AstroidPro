// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeBase.h"
#include "FireUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class ASTROIDPRO_API AFireUpgrade : public AUpgradeBase
{
	GENERATED_BODY()

	virtual void Upgrade(APlayerPawn* PlayerPawn) override;
};
