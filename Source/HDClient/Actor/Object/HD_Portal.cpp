// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/HD_Portal.h"
#include "Logic/HD_GM.h"
#include "UI/World/HeadUp/HD_UI_HeadUp_Portal.h"

#include "Components/WidgetComponent.h"

AHD_Portal::AHD_Portal()
{
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
void AHD_Portal::PortalPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
	_ui_headup_portal = Cast<UHD_UI_HeadUp_Portal>(_ui_headup->GetUserWidgetObject());
}
void AHD_Portal::PortalInit(const ERewardType e_reward_type, const FVector& v_loc_spawn)
{
	_reward_type = e_reward_type;
	switch (e_reward_type)
	{
	case ERewardType::GOLD:
		_ui_headup_portal->UIPortalSetText("Gold");
		break;
	case ERewardType::SOUL_MONSTER_WAVE:
		_ui_headup_portal->UIPortalSetText("Soul_monster");
		break;
	default:
		break;
	}
	
	SetActorLocation(v_loc_spawn);
}

void AHD_Portal::ClickedPortal()
{
	_gm->WaveNextAndStart(_reward_type);
}