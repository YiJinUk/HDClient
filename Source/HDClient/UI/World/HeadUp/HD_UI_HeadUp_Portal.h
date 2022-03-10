// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_HeadUp_Portal.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_HeadUp_Portal : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _text = nullptr;
#pragma endregion

public:
	void UIPortalSetText(const FString& str_text);
};
