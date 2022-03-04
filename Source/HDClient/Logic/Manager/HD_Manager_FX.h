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
	* VFX�� ������ �� ȣ���մϴ�
	* s_stat_vfx : vfx������ ������ �ִ� ����ü
	* v2_loc : vfx�� ������ ��ġ
	* i_id_vfx_manual : ������ ������ �������� �����Ϸ��� �ش簪�� 1�̻����� �־�� �մϴ�.(GM->IdGenerate())
	*/
	void VFXStart(FDataVFX* s_vfx, const FVector& v_loc, const FRotator& r_rot = FRotator::ZeroRotator);
#pragma endregion
};
