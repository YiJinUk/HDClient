// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/HD_Unit.h"

#include "Components/SkeletalMeshComponent.h"

AHD_Unit::AHD_Unit()
{
	PrimaryActorTick.bCanEverTick = false;

	_root_scene = CreateDefaultSubobject<USceneComponent>("_root_scene");
	if (_root_scene)
	{
		RootComponent = _root_scene;
	}

	_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>("_skeletal_mesh");
	if (_skeletal_mesh)
	{
		_skeletal_mesh->SetupAttachment(GetRootComponent());
		_skeletal_mesh->SetGenerateOverlapEvents(false);
		_skeletal_mesh->SetCanEverAffectNavigation(false);
		_skeletal_mesh->bSkipKinematicUpdateWhenInterpolating = true;
		_skeletal_mesh->bSkipBoundsUpdateWhenInterpolating = true;
		_skeletal_mesh->bComponentUseFixedSkelBounds = true;
		_skeletal_mesh->bEnableUpdateRateOptimizations = true;
		_skeletal_mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
}