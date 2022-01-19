// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileInteractableInterface.h"
#include "GameFramework/Actor.h"
#include "RockBase.generated.h"

UCLASS(Abstract)
class ASTROIDPRO_API ARockBase : public AActor, public IProjectileInteractableInterface
{
	GENERATED_BODY()
	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RockMeshComponent;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float LifeTime = 30.0f;
	
	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MovementSpeed;

	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AngularSpeed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Score;
	
	FVector IntrinsicRotationAxis;
	FVector IntrinsicMoveDirection;
public:
	// Sets default values for this actor's properties
	ARockBase();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit) override;
};
