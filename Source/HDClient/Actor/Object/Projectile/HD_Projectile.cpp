// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Projectile/HD_Projectile.h"
#include "Actor/Unit/HD_Unit.h"
#include "Actor/Unit/Monster/HD_Monster.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_GI.h"

#include "Particles/ParticleSystemComponent.h"

AHD_Projectile::AHD_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
		
	_particle = CreateDefaultSubobject<UParticleSystemComponent>("_particle");
	if (_particle)
	{
		_particle->SetupAttachment(GetRootComponent());
	}
}
void AHD_Projectile::PROJPostInit(FDataProjectile* s_data_proj)
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
	_gi = GetWorld()->GetGameInstance<UHD_GI>();

	_info_proj.speed = _gi->GetDataGame()->GetPROJSpeed();
	_info_proj.detect_range = _gi->GetDataGame()->GetPROJDetectRange();	
}
void AHD_Projectile::PROJInit(const int64 i_id, FDataProjectile* s_data_proj, const FVector& v_loc_spawn, AHD_Unit* unit_owner, AHD_Unit* unit_target, const FVector2D& v2_dest)
{
	SetActorLocation(FVector(v_loc_spawn.X, v_loc_spawn.Y, __LOC_Z));

	_info_proj.id = i_id;
	_info_proj.target = unit_target;
	_info_proj.owner = unit_owner;
	_info_proj.move_type = s_data_proj->GetPROJMoveType();
	_info_proj.attack_type = s_data_proj->GetPROJAttackType();

	if (_info_proj.move_type == EPROJMoveType::TO_STRAIGHT)
	{
		_info_proj.velocity = UHD_FunctionLibrary::GetVelocity2DByV2(GetActorLocation2D(), v2_dest);
	}
	PROJRotation();

	_info_proj.vfx = _gi->FindDataVFXByCode(s_data_proj->GetCodeVFXHit());
	PROJSetTemplate(_gi->FindDataVFXByCode(s_data_proj->GetCodeVFXPROJ()));

	PROJSetActiveTick(true);
}
void AHD_Projectile::PROJGameOverInit()
{
	
}
void AHD_Projectile::PROJSetActiveTick(bool b_is_active)
{
	if (b_is_active)
	{
		_particle->SetActive(true, true);
	}
	else
	{
		_particle->Deactivate();
		SetActorLocation(FVector(-1000.f));
	}
}
void AHD_Projectile::PROJFinish()
{
	_gm->PROJFinish(this);
}

void AHD_Projectile::PROJMoveAndAttack(const float f_delta_time)
{
	if(PROJMove(f_delta_time))
		PROJDetect();
}
bool AHD_Projectile::PROJMove(const float f_delta_time)
{
	switch (_info_proj.move_type)
	{
	case EPROJMoveType::TO_TARGET:
		if (!_info_proj.target || !_info_proj.target->GetInfoUnit().is_hit_valid)
		{
			return false;
		}
		else
		{
			_velocity_new = UHD_FunctionLibrary::GetVelocity2DByV2(GetActorLocation2D(), _info_proj.target->GetActorLocation2D()) * (_info_proj.speed * f_delta_time);
			SetActorLocation(FVector(GetActorLocation().X + _velocity_new.X, GetActorLocation().Y + _velocity_new.Y, __LOC_Z));
			PROJRotation();
		}
		break;
	case EPROJMoveType::TO_STRAIGHT:
		_velocity_new = _info_proj.velocity * (_info_proj.speed * f_delta_time);
		AddActorWorldOffset(FVector(_velocity_new.X, _velocity_new.Y, 0.f));
		//AddActorWorldOffset(FVector(0.1f,0.1f, 0.f));

		if (UHD_FunctionLibrary::GetDistance2DByVector(FVector2D(0.f), GetActorLocation2D()) >= 1500)
		{
			//세계의 중앙에서 벗어났습니다 발사체를 종료합니다
			PROJFinish();
		}
		break;
	default:
		break;
	}

	return true;
}
void AHD_Projectile::PROJDetect()
{
	switch (_info_proj.move_type)
	{
	case EPROJMoveType::TO_TARGET:
		if (UHD_FunctionLibrary::GetDistance2DByVector(GetActorLocation2D(), _info_proj.target->GetActorLocation2D()) <= _info_proj.detect_range)
		{
			/*공격가능*/
			PROJAttack(_info_proj.target);
		}
		break;
	case EPROJMoveType::TO_STRAIGHT:
	{
		if (_info_proj.owner->GetInfoUnit().unit_type == EUnitClassType::HERO)
		{
			AHD_Unit* unit_target = _gm->FindMOBNearByV2(GetActorLocation2D());
			if (unit_target && UHD_FunctionLibrary::GetDistance2DByVector(GetActorLocation2D(), unit_target->GetActorLocation2D()) <= _info_proj.detect_range)
			{
				PROJAttack(unit_target);
			}
		}
		else
		{
			if (UHD_FunctionLibrary::GetDistance2DByVector(GetActorLocation2D(), _info_proj.target->GetActorLocation2D()) <= _info_proj.detect_range)
			{
				/*공격가능*/
				PROJAttack(_info_proj.target);
			}
		}
	}
		break;
	default:
		break;
	}
}
void AHD_Projectile::PROJAttack(AHD_Unit* unit_target)
{
	switch (_info_proj.attack_type)
	{
	case EPROJAttackType::HERO_ATTACK_BASIC:
	case EPROJAttackType::MONSTER_ATTACK_BASIC:
		_info_proj.owner->UnitDoAttackBasic(unit_target);
		break;
	case EPROJAttackType::HERO_ATTACK_SKILL:
		_info_proj.owner->UnitDoAttackSK(unit_target);
		break;
	default:
		break;
	}

	PROJFinish();
}

void AHD_Projectile::PROJRotation()
{
	if (_info_proj.move_type == EPROJMoveType::TO_TARGET)
	{
		SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_proj.target->GetActorLocation()), 0.f));
	}
	else
	{
		//TO_STRAIGHT, 직선으로 날아가는 발사체는 해당함수를 한번만 호출합니다
		const FVector2D& v2_loc = GetActorLocation2D();
		SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), FVector(_info_proj.velocity.X + v2_loc.X, _info_proj.velocity.Y + v2_loc.Y, 0.f)), 0.f));
	}
}

void AHD_Projectile::PROJSetTemplate(FDataVFX* s_vfx) { if (s_vfx)		_particle->SetTemplate(s_vfx->GetCascade()); }

const FInfoProjectile& AHD_Projectile::GetInfoPROJ() { return _info_proj; }