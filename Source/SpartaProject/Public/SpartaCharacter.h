// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UWidgetComponent;

UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	UWidgetComponent* OverheadWidget;

	UFUNCTION(BlueprintPure,Category="Health")
	float GetHealth() const;

	float GetMaxHealth() const { return MaxHealth; }

	void StartSlowSpeed(float DecreasePercent,float Duration);
	FTimerHandle SlowSpeedTimerHandle;

	void StartReverseControl(float Duration);
	FTimerHandle ReverseControlTimerHandle;

	UFUNCTION(BlueprintCallable,Category="Health")
	void AddHealth(float Amount);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
	float Health;

	void OnDeath();
	void UpdateOverheadHP();

private:
	float DefaultSpeed;
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
	bool bIsNowSlow;
	void EndSlowSpeed();

	bool bIsReverseControl;
	void EndReverseControl();
	
};
