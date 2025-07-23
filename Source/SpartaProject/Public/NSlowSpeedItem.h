// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseItem.h"
#include "NSlowSpeedItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANSlowSpeedItem : public ANBaseItem
{
	GENERATED_BODY()

public:
	ANSlowSpeedItem();

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Item|Components")
	float DecreasePercent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Components")
	float Duration;

private:
	FTimerHandle DurationTimerHandle;

};
