// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "UpgradeBase.generated.h"

UCLASS(Abstract)
class ASTROIDPRO_API AUpgradeBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(Category= Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float LifeTime = 15.0f;
public:	
	// Sets default values for this actor's properties
	AUpgradeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void Upgrade(APlayerPawn* PlayerPawn);
	
	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
