// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseItem.h"
#include "NReverseControlItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANReverseControlItem : public ANBaseItem
{
	GENERATED_BODY()
	
public:
	ANReverseControlItem();

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Item")
	float Duration;
};
