// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/HD_Unit.h"
#include "Logic/Animation/HD_AM.h"

#include "Components/SkeletalMeshComponent.h"

AHD_Unit::AHD_Unit()
{
	PrimaryActorTick.bCanEverTick = false;

	_root_scene = CreateDefaultSubobject<USceneComponent>("_root_scene");
	if (_root_scene)
	{
		RootComponent = _root_scene;
	}

	_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>("_skeletal_mesh");
	if (_skeletal_mesh)
	{
		_skeletal_mesh->SetupAttachment(GetRootComponent());
		_skeletal_mesh->SetGenerateOverlapEvents(false);
		_skeletal_mesh->SetCanEverAffectNavigation(false);
		_skeletal_mesh->bSkipKinematicUpdateWhenInterpolating = true;
		_skeletal_mesh->bSkipBoundsUpdateWhenInterpolating = true;
		_skeletal_mesh->bComponentUseFixedSkelBounds = true;
		_skeletal_mesh->bEnableUpdateRateOptimizations = true;
		_skeletal_mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void AHD_Unit::UnitPostInit(const EUnitClassType e_unit_type)
{
	if(_skeletal_mesh)
		_anim_instance = Cast<UHD_AM>(_skeletal_mesh->GetAnimInstance());
	if(_anim_instance)
		_anim_instance->AMPostInit(this);

	_info_unit.unit_type = e_unit_type;
}

bool AHD_Unit::UnitUpdateAS(EAttackBasicStatus& e_atk_basic_status, int32& i_as_delay, const int32 i_as_delay_total, const uint8 i_tick_1frame)
{
	switch (e_atk_basic_status)
	{
	case EAttackBasicStatus::DETECT:
		break;
	case EAttackBasicStatus::TRY:
		if (i_as_delay < i_as_delay_total)
			i_as_delay += i_tick_1frame;
		break;
	case EAttackBasicStatus::DELAY:
		if (i_as_delay >= i_as_delay_total)
		{
			i_as_delay = 0;
			e_atk_basic_status = EAttackBasicStatus::DETECT;
		}
		else
			i_as_delay += i_tick_1frame;
		break;
	default:
		break;
	}

	if (e_atk_basic_status == EAttackBasicStatus::DETECT)
		return true;
	else
		return false;
}

FVector2D AHD_Unit::GetActorLocation2D() { FVector v_loc = GetActorLocation();	return FVector2D(v_loc.X, v_loc.Y); }
USkeletalMeshComponent* AHD_Unit::GetSkeletalMesh() { return _skeletal_mesh; }
const FInfoUnit& AHD_Unit::GetInfoUnit() { return _info_unit; }