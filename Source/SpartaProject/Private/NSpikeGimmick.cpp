// Fill out your copyright notice in the Description page of Project Settings.


#include "NSpikeGimmick.h"
#include "Components/BoxComponent.h"
#include "SpartaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ANSpikeGimmick::ANSpikeGimmick()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(SceneComp);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(Collision);

	WidgetText = TEXT("SpikeGimmick");

	Period = 3.0f;
	Duration = 3.0f;
	Damage = 30.0f;
}

void ANSpikeGimmick::DestroyGimmick()
{
	Super::DestroyGimmick();

	//ParticleComp->DestroyComponent();
}

void ANSpikeGimmick::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ANBaseGimmick::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ANBaseGimmick::OnEndOverlap);
}



