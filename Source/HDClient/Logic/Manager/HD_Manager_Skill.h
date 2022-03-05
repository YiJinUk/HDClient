// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Skill.generated.h"

class AHD_GM;
class AHD_Hero;
class AHD_Monster;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Manager_Skill : public AHD_Manager_Master
{
	GENERATED_BODY()
	
public:
	void SKPostInit(AHD_GM* gm);

	void DoSkillHero(AHD_Hero* hero, AHD_Monster* mob, const FDataSkill* s_data_sk);
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;
};
