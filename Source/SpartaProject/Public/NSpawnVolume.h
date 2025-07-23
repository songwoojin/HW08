// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NItemSpawnRow.h"
#include "NSpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ANSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ANSpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Wave")
	UDataTable* ItemDataTable;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();

	FNItemSpawnRow* GetRandomItem() const;
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume() const;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Wave")
	int32 WaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 NumToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 WaveDuration;

};
