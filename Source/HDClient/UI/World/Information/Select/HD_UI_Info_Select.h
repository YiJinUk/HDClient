// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info_Select.generated.h"

class AHD_GM;
class UHD_UI_Info_Select_Slot;
class UWrapBox;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Info_Select : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void InfoSelectPostInit();

	//웨이브가 종료될 때 호출됩니다
	void InfoSelectInit();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		UHD_UI_Info_Select_Slot* CreateWidgetSlot();
private:
	UPROPERTY(Meta = (BindWidget))
		UWrapBox* _slot_box = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	UPROPERTY()
		TArray<UHD_UI_Info_Select_Slot*> _slots;
#pragma endregion

public:
	void InfoSelectVisibleSPEC();
private:
	void ClearSlotBox();
};
