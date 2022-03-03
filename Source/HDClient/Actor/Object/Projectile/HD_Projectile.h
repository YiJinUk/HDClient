// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/HD_Object.h"
#include "HD_Projectile.generated.h"

class AHD_GM;
class AHD_Unit;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Projectile : public AHD_Object
{
	GENERATED_BODY()
#pragma region Init
public:
	AHD_Projectile();
	void PROJPostInit(FDataProjectile* s_data_proj);
	void PROJInit(const int64 i_id, const FVector& v_loc_spawn, AHD_Unit* unit_owner, AHD_Unit* unit_target, const FVector2D& v2_dest);

	void PROJSetActiveTick(bool b_is_active);

	const FInfoProjectile& GetInfoPROJ();
private:
	void PROJFinish();
protected:
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* _particle = nullptr;

	UPROPERTY()
		FInfoProjectile _info_proj;
	UPROPERTY()
		AHD_GM* _gm = nullptr;
#pragma endregion

#pragma region Move, Attack
public:
	void PROJMoveAndAttack(const float f_delta_time);
private:
	//return T : 이동에 성공했습니다
	bool PROJMove(const float f_delta_time);
	void PROJDetect();
	void PROJAttack(AHD_Unit* unit_target);

	void PROJRotation();
private:
	UPROPERTY()
		FVector2D _velocity_new = FVector2D::ZeroVector;
#pragma endregion
};
