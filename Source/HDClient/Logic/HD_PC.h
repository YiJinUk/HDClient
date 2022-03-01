// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HD_PC.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_PC : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void PCPostInit();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void PCBPPostInit();
#pragma endregion
};
