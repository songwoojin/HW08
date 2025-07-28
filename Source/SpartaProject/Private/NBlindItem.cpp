// Fill out your copyright notice in the Description page of Project Settings.


#include "NBlindItem.h"
#include "SpartaPlayerController.h"
#include "SpartaCharacter.h"

ANBlindItem::ANBlindItem()
{
	ItemType = FName("Blind");
	Duration = 5.0f;
}

void ANBlindItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPlayerController->GetPawn()))
			{
				SpartaCharacter->StartBlind(Duration);

				DestroyItem();
			}
		}
	}
}
