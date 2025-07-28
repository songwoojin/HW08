// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseGimmick.h"
#include "NSpikeGimmick.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANSpikeGimmick : public ANBaseGimmick
{
	GENERATED_BODY()
	
public:
	ANSpikeGimmick();

	virtual void DestroyGimmick() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* Collision;

};
