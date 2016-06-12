// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */


UCLASS()
class JUNE13_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
	ALobbyGameMode(const class FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapTravel) //https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Properties/index.html
	TArray<FString> ValidMapNames;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapTravel)
	TArray<FString> ValidMapModes;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
