// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Animation/HD_AM.h"
#include "HD_AM_Companion.generated.h"

class AHD_Companion;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_AM_Companion : public UHD_AM
{
	GENERATED_BODY()

public:
	void AMPostInitChild(AHD_Unit* unit_owner) override;
private:
	UPROPERTY()
		AHD_Companion* _owner = nullptr;

public:
	UFUNCTION(BlueprintCallable)
		void AttackBasicNotify();
	UFUNCTION(BlueprintCallable)
		void AttackSKNotify();
};
