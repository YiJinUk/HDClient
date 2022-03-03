// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HD_AM.generated.h"

class AHD_Unit;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_AM : public UAnimInstance
{
	GENERATED_BODY()


public:
	void AMPostInit(AHD_Unit* unit_owner);
protected:
	virtual void AMPostInitChild(AHD_Unit* unit_owner);
};
