// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/HD_Unit.h"
#include "Logic/Animation/HD_AM.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_GI.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

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

	//_ui_headup = object_initializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("_ui_headup"));
	_ui_headup = CreateDefaultSubobject<UWidgetComponent>("_ui_headup");
	if (_ui_headup)
	{
		_ui_headup->SetupAttachment(GetRootComponent());
		_ui_headup->SetGenerateOverlapEvents(false);
		_ui_headup->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_ui_headup->CanCharacterStepUpOn = ECB_No;
		_ui_headup->SetWidgetSpace(EWidgetSpace::Screen);
		_ui_headup->SetDrawAtDesiredSize(true);
	}
}

void AHD_Unit::UnitPostInit(AHD_PC* pc, const EUnitClassType e_unit_type)
{
	if(_skeletal_mesh)
		_anim_instance = Cast<UHD_AM>(_skeletal_mesh->GetAnimInstance());
	if(_anim_instance)
		_anim_instance->AMPostInit(this);
	_gi = GetWorld()->GetGameInstance<UHD_GI>();
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
	_pc = pc;

	_info_unit.unit_type = e_unit_type;
}
void AHD_Unit::UnitSetActiveTick(const bool b_is_active)
{
	if (b_is_active)
	{

	}
	else
	{
		SetActorLocation(FVector(-1500.f));
	}
	UnitSetActiveTickChild(b_is_active);
}
void AHD_Unit::UnitSetActiveTickChild(const bool b_is_active)
{
	//override
}

void AHD_Unit::UnitAddBF(const int64 i_gid_bf) { _info_unit.gid_bfs.Add(i_gid_bf); }
void AHD_Unit::UnitRemoveBF(const int64 i_gid_bf) { _info_unit.gid_bfs.Remove(i_gid_bf); }

void AHD_Unit::UnitSetDMG(int32& i_dmg, const int32 i_value)
{
	i_dmg += i_value;
	if (i_dmg <= 0)
		i_dmg = 0;
}
void AHD_Unit::UnitSetAS(int32& i_as_delay, const int32 i_as_delay_total, const int32 i_tick_1frame)
{
	if (i_as_delay < i_as_delay_total)
		i_as_delay += i_tick_1frame;
	if (i_as_delay <= 0)
		i_as_delay = 0;
}
void AHD_Unit::UnitSetHP(int32& i_hp, const int32 i_hp_max, const int32 i_value)
{
	i_hp += i_value;
	if (i_hp <= 0)
	{
		i_hp = 0;
	}
	else if (i_hp > i_hp_max)
	{
		i_hp = i_hp_max;
	}
}
void AHD_Unit::UnitSetCooldown(int32& i_cooldown_tick, const int32 i_cooldown_tick_max, const int32 i_tick_1frame)
{
	if (i_cooldown_tick < i_cooldown_tick_max)
		i_cooldown_tick += i_tick_1frame;
	if (i_cooldown_tick <= 0)
		i_cooldown_tick = 0;
}

void AHD_Unit::UnitHit(const FBattleHitResult& s_battle_hit_result) {	/*override*/ }
void AHD_Unit::UnitDeath() {	/*override*/ }

void AHD_Unit::UnitDoAttackBasic(AHD_Unit* unit_target) {/*override*/ }
void AHD_Unit::UnitDoAttackSK(AHD_Unit* unit_target) {	/*override*/ }
void AHD_Unit::UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value) {	/*override*/ }
const int32 AHD_Unit::UnitGetStat(const EUnitStatType e_stat_type) { return int32(); /*override*/ };
FVector2D AHD_Unit::GetActorLocation2D() { FVector v_loc = GetActorLocation();	return FVector2D(v_loc.X, v_loc.Y); }
USkeletalMeshComponent* AHD_Unit::GetSkeletalMesh() { return _skeletal_mesh; }
const FInfoUnit& AHD_Unit::GetInfoUnit() { return _info_unit; }