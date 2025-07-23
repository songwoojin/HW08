// Fill out your copyright notice in the Description page of Project Settings.


#include "NSlowSpeedItem.h"
#include "SpartaPlayerController.h"
#include "SpartaCharacter.h"

ANSlowSpeedItem::ANSlowSpeedItem()
{
	ItemType = FName("SlowSpeed");
	DecreasePercent = 50.0f;
	Duration = 5;
}

void ANSlowSpeedItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPlayerController->GetPawn()))
			{
				SpartaCharacter->StartSlowSpeed(DecreasePercent, Duration);

				DestroyItem();
			}
		}
	}

}
