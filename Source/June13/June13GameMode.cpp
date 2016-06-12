// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "June13GameMode.h"

DEFINE_LOG_CATEGORY(YourLog); //Requires DEFINE_LOG_EXTERN from .h

AJune13GameMode::AJune13GameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bStartPlayersAsSpectators = true;

	UE_LOG(YourLog, Warning, TEXT("Constructor for AJune13GameMode (UE_LOG)")); //Window->Output Log to show log

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Constructor for AJune13GameMode"));
	}

}

void AJune13GameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("AJune13GameMode::StartPlay"));
	}


}

