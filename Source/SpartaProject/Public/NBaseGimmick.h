// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBaseGimmick.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ANBaseGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	ANBaseGimmick();

	FTimerHandle UIDuration;

	UFUNCTION()
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	virtual void DestroyGimmick();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Component")
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, Category = "Component")
	UParticleSystemComponent* ParticleComp;


	UPROPERTY(EditAnywhere, Category = "Setting")
	float Period;

	UPROPERTY(EditAnywhere, Category = "Setting")
	float Duration;

	UPROPERTY(EditAnywhere, Category = "Setting")
	float Damage;

	FTimerHandle PeroidTimerHandle;
	bool bIsSpike;
	virtual void StartPeriod();
	void EndPeriod();

	FTimerHandle DurationTimerHandle;
	void StartDuration();
	void EndDuration();

	void ShowUI();
	FName WidgetText;

	bool bIsOverlapping;

	void DamageActorWhileOverlapping();
	FTimerHandle DamageTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Setting")
	float DamageDuration;

};
