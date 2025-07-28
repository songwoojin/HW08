// Fill out your copyright notice in the Description page of Project Settings.


#include "NBaseGimmick.h"
#include "Components/BoxComponent.h"
#include "SpartaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SpartaPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

ANBaseGimmick::ANBaseGimmick()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	bIsSpike = true;
	bIsOverlapping = false;

	DamageDuration = 1.0;
}

// Called when the game starts or when spawned
void ANBaseGimmick::BeginPlay()
{
	Super::BeginPlay();

	StartPeriod();

}

void ANBaseGimmick::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(OtherActor))
	{
		bIsOverlapping = true;
	}
}

void ANBaseGimmick::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(OtherActor))
	{
		bIsOverlapping = false;
	}
}

void ANBaseGimmick::StartPeriod()
{
	GetWorldTimerManager().SetTimer(
		PeroidTimerHandle,
		this,
		&ANBaseGimmick::EndPeriod,
		Period,
		false
	);

	if (ParticleComp)
	{
		ParticleComp->ActivateSystem(true);
	}

	DamageActorWhileOverlapping();

	GetWorldTimerManager().SetTimer(
		DamageTimerHandle,
		this,
		&ANBaseGimmick::DamageActorWhileOverlapping,
		DamageDuration,
		true
	);

	ShowUI();
}

void ANBaseGimmick::EndPeriod()
{
	bIsSpike = false;

	GetWorldTimerManager().ClearTimer(DamageTimerHandle);

	StartDuration();
}

void ANBaseGimmick::StartDuration()
{
	GetWorldTimerManager().SetTimer(
		DurationTimerHandle,
		this,
		&ANBaseGimmick::EndDuration,
		Duration,
		false
	);

	if (ParticleComp)
	{
		ParticleComp->DeactivateSystem();
	}
}

void ANBaseGimmick::EndDuration()
{
	bIsSpike = true;

	StartPeriod();
}

void ANBaseGimmick::ShowUI()
{
	APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PC)	return;

	ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC);
	if (!SpartaPC)	return;

	if (!IsValid(SpartaPC->GetGimmickWidget()))	return;

	UUserWidget* GimmickWidget = Cast<UUserWidget>(SpartaPC->GetGimmickWidget());
	if (IsValid(GimmickWidget))
	{
		if (UTextBlock* MyText = Cast<UTextBlock>(GimmickWidget->GetWidgetFromName(WidgetText)))
		{
			TWeakObjectPtr<UTextBlock> WeakText = MyText;

			//UE_LOG(LogTemp, Warning, TEXT("Gimmick UI Activate"));

			// 보이게 만들기
			WeakText->SetVisibility(ESlateVisibility::Visible);

			GetWorldTimerManager().SetTimer(
				UIDuration,
				FTimerDelegate::CreateLambda([WeakText]()
			{
						if (WeakText.IsValid())
						{
							WeakText->SetVisibility(ESlateVisibility::Hidden);
						}
			}),
				2.0f,
				false
			);

		}
	}
}

void ANBaseGimmick::DamageActorWhileOverlapping()
{
	if (bIsOverlapping)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			if (ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC))
			{
				if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPC->GetPawn()))
				{
					UGameplayStatics::ApplyDamage(SpartaCharacter, Damage, nullptr, this, UDamageType::StaticClass());
				}
			}
		}
	}
}

void ANBaseGimmick::DestroyGimmick()
{
	Destroy();
}


