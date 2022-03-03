// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "GameFramework/Actor.h"
#include "HD_Object.generated.h"

UCLASS()
class HDCLIENT_API AHD_Object : public AActor
{
	GENERATED_BODY()
	
public:	
	AHD_Object();
protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _root_scene = nullptr;

};
