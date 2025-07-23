// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBaseItem.h"
#include "NMineItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ANMineItem : public ANBaseItem
{
	GENERATED_BODY()
	
public:
	ANMineItem();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Collision")
	USphereComponent* ExplosionCollision;

	void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USoundBase* ExplosionSound;

	bool bHasExploded;

private:
	void Explode();

	FTimerHandle ExplosionTimerHandle;


};
