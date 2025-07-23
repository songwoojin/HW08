// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseItem.h"
#include "NHealingItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANHealingItem : public ANBaseItem
{
	GENERATED_BODY()

public:
	ANHealingItem();

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	int32 HealAmount;
};
