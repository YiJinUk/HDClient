// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Friend/Companion/HD_Companion.h"
#include "HD_CPAN00001.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_CPAN00001 : public AHD_Companion
{
	GENERATED_BODY()
	
private:
	void CPANAttackSKNotify() override;
};
