// Fill out your copyright notice in the Description page of Project Settings.


#include "NHealingItem.h"
#include "SpartaCharacter.h"

ANHealingItem::ANHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void ANHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (Activator && Activator->ActorHasTag("Player"))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player Gained %d HP!"), HealAmount));

		if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}

		DestroyItem();
	}
}
