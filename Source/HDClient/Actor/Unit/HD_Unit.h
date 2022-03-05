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
	* ������ ���Ⱥ����� ����ϴ� �Լ��Դϴ�. ��� ������ �ش� �Լ��� ���ľ� �մϴ�
	* @param e_stat_type - ����� ����
	* @param e_stat_by - ������ ������ ��ü. (Ư��, ����, ��, ���� ���)
	* @param i_value - �ش� ����ŭ ����� ���ȿ� ���մϴ�
	*/
	virtual void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value);
	virtual const int32 UnitGetStat(const EUnitStatType e_stat_type);
#pragma endregion
};
