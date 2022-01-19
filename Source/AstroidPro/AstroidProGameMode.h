// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AstroidProGameMode.generated.h"

UCLASS(MinimalAPI)
class AAstroidProGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 GameScore = 0;

public:
	AAstroidProGameMode();

	UFUNCTION(BlueprintCallable)
	int32 GetGameScore() const;

	UFUNCTION(BlueprintCallable)
	void AddGameScore(int32 Score);

	UFUNCTION(BlueprintNativeEvent)
	void DoGameOver();
	virtual void DoGameOver_Implementation();
};



