# Asteroid Pro: Software Architecture analysis

This documentation will discuss the code architecture in the game.

## Interface abstraction

Interaction between Actor pairs is complicated. If we list the 1-to-1 behavior for each pair of actors, it ended up with an O(N) space complexity for the code in one place. To give good scalability in interaction logic, I assume that these actors should be self-contained to finish their interaction logic. So I choose to use an interface to abstract out the ability to interact, without knowing the exact implementation of interaction.

```c++
// You can see the code: Source/Public/ProjectileInteractableInterface.h:20
class ASTROIDPRO_API IProjectileInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnProjectileInteract(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit);

    // Notice that this is a virtual function that has default implementation
    // and we can call Super:: as well!
    // POWER OF REFLECTION SYSTEM & BLUEPRINT VM
    // this works very differently than interfaces in C#!
	virtual void OnProjectileInteract_Implementation(AAstroidProProjectile* TargetProjectile, const FHitResult& Hit);
};

```

So with the power of the Unreal reflection system, I can easily mask out all other actors that do not need to interact with the projectile and write different implementations for the rocks in different places:

- `ARockBase::OnProjectileInteract_Implementation()`: add score
- `SmallRock::OnProjectileInteract_Implementation()`: drop upgrade
- `BigRock::OnProjectileInteract_Implementation()`: split to others

all can be freely inherited and executed by a single call: 

```c++
IProjectileInteractableInterface::Execute_OnProjectileInteract(OtherActor, this, Hit);
```

## Data-oriented programming

A quick question: what is the essence of Blueprint? Many think BP is a place where they can do visual scripting. Unfortunately, that is not a good enough answer. In the implementation, BPs are not different from other `.uasset` files: they are just serialized data on the disk (the magic is on the BP VM parser to read the code inside). Well, we can make use of this! In my design architecture, Blueprints are just used as data-only assets that can be easily fine-tuned (good support on visualization, no need to re-compiled by UBT/UHT). All the control logic is running inside the C++ code where the reflection system will support the type inheritance between the data asset with the original base. 

This helps me make quick adjustments on playtesting control parameters, spawning parameters, and can easily recombine the types using the `TSubclassOf<>` pointer.

## A Natural Singleton: `AGameMode`

We all want there to be one and only one **manager** that control the main game logic, so that's goes with the singleton pattern. In Unreal Engine, the `AGameMode` is exactly designed and used for the case: A only-one controller that has overall authority through the `UWorld`. So I just put the scoring logic there. Plus: `UWorld` helps me deal with instantiation problems with singleton so no worry :) 

Yet, for now, we have only one map that needs to play. If the game logic needs to be shared across different `AGameMode` that behaves very differently, I may want to choose to program a `GameInstanceSubsystem`. 
