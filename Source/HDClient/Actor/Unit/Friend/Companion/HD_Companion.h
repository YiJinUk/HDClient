// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Friend/HD_Friend.h"
#include "HD_Companion.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Companion : public AHD_Friend
{
	GENERATED_BODY()
	
public:
	void CPANPostInit(FDataCPAN* s_data_cpan);
	void CPANInit(const FVector& v_loc_spawn);
	const FInfoCPAN& GetInfoCPAN();
private:
	UPROPERTY()
		FInfoCPAN _info_cpan;
};
