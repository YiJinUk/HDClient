// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Monster/HD_Monster.h"
#include "HD_MOB01001.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_MOB01001 : public AHD_Monster
{
	GENERATED_BODY()
	
protected:
	void MOBAttackBasic() override;
};
