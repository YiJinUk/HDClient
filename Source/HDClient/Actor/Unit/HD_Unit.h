// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "GameFramework/Actor.h"
#include "HD_Unit.generated.h"

class UHD_AM;
class UHD_AM_Hero;

UCLASS()
class HDCLIENT_API AHD_Unit : public AActor
{
	GENERATED_BODY()
	
#pragma region Init
public:	
	AHD_Unit();
	void UnitPostInit();

	USkeletalMeshComponent* GetSkeletalMesh();
protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _root_scene = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* _skeletal_mesh = nullptr;
#pragma endregion

public:
	FVector2D GetActorLocation2D();
protected:
	UPROPERTY()
		UHD_AM* _anim_instance = nullptr;
};
