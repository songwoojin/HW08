// Fill out your copyright notice in the Description page of Project Settings.


#include "NSpawnVolume.h"
#include "Components/BoxComponent.h"
#include "NBaseGimmick.h"

ANSpawnVolume::ANSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;

	WaveIndex = 0;
	NumToSpawn = 0;
	WaveDuration = 0;
}

FVector ANSpawnVolume::GetRandomPointInVolume(bool bIsGimmick) const
{
	//길이의 절반
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	//중심값
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin+FVector(
		FMath::FRandRange(-BoxExtent.X,BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y), 
		bIsGimmick? -BoxExtent.Z : FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));
}

AActor* ANSpawnVolume::SpawnRandomItem()
{
	if (FNItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

FNItemSpawnRow* ANSpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable)	return nullptr;

	TArray<FNItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));

	ItemDataTable->GetAllRows(ContextString,AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FNItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for (FNItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

AActor* ANSpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass)	return nullptr;

	bool bIsGimmick = false;

	//자식관
	if (ItemClass.Get()->IsChildOf(ANBaseGimmick::StaticClass()))
	{
		bIsGimmick = true;
	}

	//FActorSpawnParameters Params;
	//Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedActor=GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(bIsGimmick),
		FRotator::ZeroRotator
	);

	return SpawnedActor;

}



