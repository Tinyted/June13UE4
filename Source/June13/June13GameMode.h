// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "June13GameMode.generated.h"


/**
 * 
 */
UCLASS()
class JUNE13_API AJune13GameMode : public AGameMode
{
	GENERATED_BODY()
	
	AJune13GameMode(const class FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;
	
	
};
