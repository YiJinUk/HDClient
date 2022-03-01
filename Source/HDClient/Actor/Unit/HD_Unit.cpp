// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/HD_Unit.h"

// Sets default values
AHD_Unit::AHD_Unit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHD_Unit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHD_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

