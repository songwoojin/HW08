// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseItem.h"
#include "NCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANCoinItem : public ANBaseItem
{
	GENERATED_BODY()

public:
	ANCoinItem();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	int32 PointValue;

	virtual void ActivateItem(AActor* Activator) override;
};
