// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "NSpawnVolume.h"
#include "NCoinItem.h"
#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "NBaseItem.h"
#include "SpartaCharacter.h"

ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

void ASpartaGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowMainMenu(true);
		}
	}
}

void ASpartaGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	StartWave();
}

void ASpartaGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		//EndLevel();

		EndWave();
	}
}

void ASpartaGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		//레벨 바뀔 때 게임스테이트도 다시 생성
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void ASpartaGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController);
		if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
		{
			if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
			{
				//float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
				float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
			}

			if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
			{
				if (UGameInstance* GameInstance = GetGameInstance())
				{
					USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
					if (SpartaGameInstance)
					{
						ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
					}
				}
			}

			if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
			{
				LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), CurrentLevelIndex + 1)));
			}

			if (UTextBlock* HPText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("HP"))))
			{
				if (APawn* Pawn = SpartaPlayerController->GetPawn())
				{
					if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(Pawn))
					{
						HPText->SetText(FText::FromString(FString::Printf(TEXT("HP : %.1f / %.1f"),SpartaCharacter->GetHealth(),SpartaCharacter->GetMaxHealth())));
					}
				}
			}

			if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
			{
				WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave : %d"), CurWave + 1)));
			}

			if (UTextBlock* CoinText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Coin"))))
			{
				CoinText->SetText(FText::FromString(FString::Printf(TEXT("Coin : %d / %d"), CollectedCoinCount,SpawnedCoinCount)));
			}

			if (UTextBlock* SlowSpeedText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("SlowSpeed"))))
			{
				if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPlayerController->GetPawn()))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(SpartaCharacter->SlowSpeedTimerHandle);
					if (RemainingTime < 0.f)
					{
						RemainingTime = 0.f;
					}
					SlowSpeedText->SetText(FText::FromString(FString::Printf(TEXT("Slow Speed debuff remaining time : %.1f"), RemainingTime)));
				}
			}

			if (UTextBlock* ReverseControlText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("ReverseControl"))))
			{
				if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPlayerController->GetPawn()))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(SpartaCharacter->ReverseControlTimerHandle);
					if (RemainingTime < 0.f)
					{
						RemainingTime = 0.f;
					}
					ReverseControlText->SetText(FText::FromString(FString::Printf(TEXT("Reverse control debuff remaining time : %.1f"), RemainingTime)));
				}
			}
		}
	}
}

void ASpartaGameState::StartWave()
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANSpawnVolume::StaticClass(), FoundVolumes);

	ANSpawnVolume* WaveSpawnVolume = nullptr;

	//Find Wave
	if (FoundVolumes.Num() == 0)	return;

	for (AActor* FoundVolume : FoundVolumes)
	{
		if (ANSpawnVolume* SpawnVolume = Cast<ANSpawnVolume>(FoundVolume))
		{
			if (SpawnVolume->WaveIndex == CurWave)
			{
				WaveSpawnVolume = SpawnVolume;
				break;
			}
		}
	}

	if (WaveSpawnVolume == nullptr)
	{
		OnGameOver();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start"), CurWave+1);

	const int32 ItemToSpawn = WaveSpawnVolume->NumToSpawn;

	//Spawned Item
	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ANSpawnVolume* SpawnVolume = Cast<ANSpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ANCoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&ASpartaGameState::OnWaveTimeUp,
		WaveSpawnVolume->WaveDuration,
		false
	);
}

void ASpartaGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANBaseItem::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (ANBaseItem* Item=Cast<ANBaseItem>(Actor))
		{
			Item->Destroy();
		}
	}

	CurWave++;

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	StartWave();
}

void ASpartaGameState::OnWaveTimeUp()
{
	OnGameOver();
}
