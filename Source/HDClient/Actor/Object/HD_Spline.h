// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/HD_Object.h"
#include "HD_Spline.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Spline : public AHD_Object
{
	GENERATED_BODY()
protected:
	AHD_Spline();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USplineComponent* _spline = nullptr;

public:
	USplineComponent* GetSplineComponent() const;
};
