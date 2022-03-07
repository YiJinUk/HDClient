// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Buff.generated.h"

class UHD_GI;
class AHD_GM;
class AHD_Unit;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Manager_Buff : public AHD_Manager_Master
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void BFPostInit(AHD_GM* gm, UHD_GI* gi);
private:
	FInfoBuff* GetInfoBF();
	void AddInfoBF(FInfoBuff* s_info_bf);
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	UPROPERTY()
		TArray<FInfoBuff> _pool_bf_origin;
	TArray<FInfoBuff*> _pool_bf;

	/*
	* 생성된 모든 버프를 가지고 있습니다
	* key : gid, value : 사용중인 버프객체
	*/	
	TMap<int64, FInfoBuff*> _active_bfs;
#pragma endregion

#pragma region Buff
public:
	/*
	* 버프를 캐스팅합니다
	* @param str_code_bf : 캐스팅할 버프의 코드입니다
	* @param caster : 캐스팅할 유닛 입니다
	* @param casted : 피캐스터. 캐스팅 당할 유닛입니다
	* @param e_bf_phase : 버프의 효과발동 시점입니다
	* @param e_bf_timer : 버프의 생명주기의 종류입니다
	* @param i_life : 버프의 생명주기값 입니다. e_bf_timer변수에 따라서 역할이 달라집니다
	* @param e_bf_overlap : 동일한 코드의 버프가 부여될 때 처리방법 종류입니다
	* @param str_unique : 버프의 고유문자입니다. 버프가 중복적용을 판단할 때 사용됩니다
	* @param i_value : 버프에 부여할 수치입니다
	*/
	void BFCastStart(const FString& str_code_bf, AHD_Unit* caster, AHD_Unit* casted, 
		const EBuffPhase e_bf_phase, const EBuffTimer e_bf_timer, const int32 i_life, const EBuffOverlap e_bf_overlap, const FString& str_unique,
		const int32 i_value_1 = 0, const int32 i_value_2 = 0, const int32 i_value_3 = 0);

	void BFCasting(FInfoBuff* s_info_bf);

	void BFTick();
private:
	bool BFCanOverlap(AHD_Unit* casted, const EBuffOverlap e_bf_overlap, const FString& str_unique);
	void BFInit(FInfoBuff* s_info_bf_new, const FString& str_code_bf, AHD_Unit* caster, AHD_Unit* casted,
		const EBuffPhase e_bf_phase, const EBuffTimer e_bf_timer, const int32 i_life, const EBuffOverlap e_bf_overlap, const FString& str_unique,
		const int32 i_value_1, const int32 i_value_2, const int32 i_value_3);

	void BFEnd(FInfoBuff* s_info_bf);
	void BFFinish(FInfoBuff* s_info_bf);
#pragma endregion
};
