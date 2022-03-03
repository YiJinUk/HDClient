// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/HD_Object.h"

AHD_Object::AHD_Object()
{
	PrimaryActorTick.bCanEverTick = false;

	_root_scene = CreateDefaultSubobject<USceneComponent>("_root_scene");
	if (_root_scene)
	{
		RootComponent = _root_scene;
	}
}

FVector2D AHD_Object::GetActorLocation2D() { FVector v_loc = GetActorLocation();	return FVector2D(v_loc.X, v_loc.Y); }