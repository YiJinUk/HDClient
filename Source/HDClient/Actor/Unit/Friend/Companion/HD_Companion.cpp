// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/Companion/HD_Companion.h"

void AHD_Companion::CPANPostInit(FDataCPAN* s_data_cpan)
{
	_info_cpan.code = s_data_cpan->GetCode();
}
void AHD_Companion::CPANInit(const FVector& v_loc_spawn)
{
	UnitSetActiveTick(true);
	SetActorLocation(v_loc_spawn);
}
const FInfoCPAN& AHD_Companion::GetInfoCPAN() { return _info_cpan; }