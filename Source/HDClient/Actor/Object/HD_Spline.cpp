// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/HD_Spline.h"
#include "Components/SplineComponent.h"

AHD_Spline::AHD_Spline()
{
	_spline = CreateDefaultSubobject<USplineComponent>("_spline");
	_spline->SetupAttachment(GetRootComponent());
}

USplineComponent* AHD_Spline::GetSplineComponent() const { return _spline; }

