// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_FX.generated.h"

class UHD_GI;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Manager_FX : public AHD_Manager_Master
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void FXPostInit(UHD_GI* gi);
#pragma endregion

#pragma region VFX
public:
	/*
	* VFX를 생성할 때 호출합니다
	* s_stat_vfx : vfx정보를 가지고 있는 구조체
	* v2_loc : vfx를 생성할 위치
	* i_id_vfx_manual : 버프의 삭제를 수동으로 관여하려면 해당값을 1이상으로 넣어야 합니다.(GM->IdGenerate())
	*/
	void VFXStart(FDataVFX* s_vfx, const FVector& v_loc, const FRotator& r_rot = FRotator::ZeroRotator);
#pragma endregion
};
