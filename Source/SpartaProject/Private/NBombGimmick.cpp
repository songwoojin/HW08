// Fill out your copyright notice in the Description page of Project Settings.


#include "NBombGimmick.h"
#include "Components/SphereComponent.h"
#include "SpartaCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ANBombGimmick::ANBombGimmick()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(SceneComp);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(Collision);

	WidgetText = TEXT("BombGimmick");

	Period = 0.1f;
	Duration = 3.0f;
	Damage = 20.0f;
}

void ANBombGimmick::DestroyGimmick()
{
	Super::DestroyGimmick();
}

void ANBombGimmick::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ANBaseGimmick::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ANBaseGimmick::OnEndOverlap);
}

