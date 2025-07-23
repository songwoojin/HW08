// Fill out your copyright notice in the Description page of Project Settings.


#include "NCoinItem.h"
#include "Engine/World.h"
#include "SpartaGameState.h"

ANCoinItem::ANCoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ANCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player Gained %d Points!"),PointValue));
		if (UWorld* World = GetWorld())
		{
			if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
			}
		}

		DestroyItem();
	}
}
