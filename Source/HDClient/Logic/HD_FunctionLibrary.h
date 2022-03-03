// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HD_FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static void GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color = FColor::Magenta);
};
