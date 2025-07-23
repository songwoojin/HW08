// Fill out your copyright notice in the Description page of Project Settings.


#include "NReverseControlItem.h"
#include "SpartaPlayerController.h"
#include "SpartaCharacter.h"

ANReverseControlItem::ANReverseControlItem()
{
	ItemType = FName("ReverseControl");
	Duration = 3.0f;
}

void ANReverseControlItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPlayerController->GetPawn()))
			{
				SpartaCharacter->StartReverseControl(Duration);

				DestroyItem();
			}
		}
	}
}
