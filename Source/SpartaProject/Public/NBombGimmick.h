// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseGimmick.h"
#include "NBombGimmick.generated.h"

/**
 * 
 */
class USphereComponent;

UCLASS()
class SPARTAPROJECT_API ANBombGimmick : public ANBaseGimmick
{
	GENERATED_BODY()

public:
	ANBombGimmick();

	virtual void DestroyGimmick() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* Collision;
	
};
