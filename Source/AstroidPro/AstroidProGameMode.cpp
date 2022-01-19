// Copyright Epic Games, Inc. All Rights Reserved.

#include "AstroidProGameMode.h"
#include "AstroidProPawn.h"

AAstroidProGameMode::AAstroidProGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAstroidProPawn::StaticClass();
}

int32 AAstroidProGameMode::GetGameScore() const
{
	return GameScore;
}

void AAstroidProGameMode::AddGameScore(int32 Score)
{
	GameScore += Score;
}

void AAstroidProGameMode::DoGameOver_Implementation()
{
	
}

