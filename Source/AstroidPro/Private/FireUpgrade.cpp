// Fill out your copyright notice in the Description page of Project Settings.


#include "FireUpgrade.h"

void AFireUpgrade::Upgrade(APlayerPawn* PlayerPawn)
{
	PlayerPawn->UpgradeFire();
}
