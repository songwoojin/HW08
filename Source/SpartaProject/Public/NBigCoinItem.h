// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NCoinItem.h"
#include "NBigCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANBigCoinItem : public ANCoinItem
{
	GENERATED_BODY()

public:
	ANBigCoinItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
