// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RockSpawnerComponent.generated.h"


class ARockBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTROIDPRO_API URockSpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true));
	TArray<TSubclassOf<ARockBase>> RockTypes;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float SpawningRadius;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float SpawningRate;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MaxSpawnInOneShot;

	uint32 bCanSpawn : 1;

	FTimerHandle TimerHandle_ResetSpawn;
	
	public:	
	// Sets default values for this component's properties
	URockSpawnerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SpawnRocks();
	void ResetSpawn();
};
