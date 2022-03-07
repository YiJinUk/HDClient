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
	* ������ ��� ������ ������ �ֽ��ϴ�
	* key : gid, value : ������� ������ü
	*/	
	TMap<int64, FInfoBuff*> _active_bfs;
#pragma endregion

#pragma region Buff
public:
	/*
	* ������ ĳ�����մϴ�
	* @param str_code_bf : ĳ������ ������ �ڵ��Դϴ�
	* @param caster : ĳ������ ���� �Դϴ�
	* @param casted : ��ĳ����. ĳ���� ���� �����Դϴ�
	* @param e_bf_phase : ������ ȿ���ߵ� �����Դϴ�
	* @param e_bf_timer : ������ �����ֱ��� �����Դϴ�
	* @param i_life : ������ �����ֱⰪ �Դϴ�. e_bf_timer������ ���� ������ �޶����ϴ�
	* @param e_bf_overlap : ������ �ڵ��� ������ �ο��� �� ó����� �����Դϴ�
	* @param str_unique : ������ ���������Դϴ�. ������ �ߺ������� �Ǵ��� �� ���˴ϴ�
	* @param i_value : ������ �ο��� ��ġ�Դϴ�
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
