// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_FX.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AHD_Manager_FX::FXPostInit(UHD_GI* gi)
{

}

void AHD_Manager_FX::VFXStart(FDataVFX* s_vfx, const FVector2D& v2_loc, const FRotator& r_rot)
{
	if (!s_vfx) return;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), s_vfx->GetCascade(), FVector(v2_loc.X, v2_loc.Y, 0.f), r_rot, FVector(s_vfx->GetSize()));
}