// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "GameFramework/Actor.h"
#include "HD_Unit.generated.h"

class UHD_AM;
class UHD_AM_Hero;
class AHD_GM;

UCLASS()
class HDCLIENT_API AHD_Unit : public AActor
{
	GENERATED_BODY()
	
#pragma region Init
public:	
	AHD_Unit();
	void UnitPostInit(const EUnitClassType e_unit_type);
	void UnitSetActiveTick(const bool b_is_active);

	FVector2D GetActorLocation2D();
	USkeletalMeshComponent* GetSkeletalMesh();
	const FInfoUnit& GetInfoUnit();
protected:
	virtual void UnitSetActiveTickChild(const bool b_is_active);
protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _root_scene = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* _skeletal_mesh = nullptr;

	UPROPERTY()
		UHD_AM* _anim_instance = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;

	UPROPERTY()
		FInfoUnit _info_unit;
#pragma endregion

#pragma region Attack
public:
	virtual void UnitDoAttackBasic(AHD_Unit* unit_target);
protected:
	bool UnitUpdateAS(EAttackBasicStatus& e_atk_basic_status, int32& i_as_delay, const int32 i_as_delay_total, const uint8 i_tick_1frame);
#pragma endregion

#pragma region Death
public:
	virtual void UnitDeath();
#pragma endregion

#pragma region Stat
public:
	/*
	* 유닛의 스탯변경을 담당하는 함수입니다. 모든 스탯은 해당 함수를 거쳐야 합니다
	* @param e_stat_type - 변경될 스탯
	* @param e_stat_by - 스탯을 변경한 주체. (특성, 버프, 적, 영웅 등등)
	* @param i_value - 해당 값만큼 변경될 스탯에 더합니다
	*/
	virtual void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value);
	virtual const int32 UnitGetStat(const EUnitStatType e_stat_type);
#pragma endregion
};
