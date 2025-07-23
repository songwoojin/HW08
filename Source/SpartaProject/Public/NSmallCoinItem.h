// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NCoinItem.h"
#include "NSmallCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANSmallCoinItem : public ANCoinItem
{
	GENERATED_BODY()

public:
	ANSmallCoinItem();

	virtual void ActivateItem(AActor* Activator) override;

protected:

	
};
