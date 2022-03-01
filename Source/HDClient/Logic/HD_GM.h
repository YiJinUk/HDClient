// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HD_GM.generated.h"

class AHD_PC;
class AHD_Hero;
class AHD_MagicStone;
class AHD_Companion;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_GM : public AGameModeBase
{
	GENERATED_BODY()
	

#pragma region Init
protected:
	AHD_GM();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
private:
	//어플 실행후 첫 호출지점입니다
	void GMPostInit();
private:
	UPROPERTY()
		bool _is_call_PostLogin = false;
	UPROPERTY()
		bool _is_call_BeginPlay = false;
#pragma endregion

#pragma region Player
private:
	UPROPERTY()
		AHD_PC* _pc = nullptr;
	UPROPERTY()
		AHD_Hero* _hero = nullptr;
#pragma endregion

#pragma region MagicStone
private:
	AHD_MagicStone* _ms = nullptr;
#pragma endregion
#pragma region Companion
private:
	AHD_Companion* _cpan = nullptr;
#pragma endregion
};
