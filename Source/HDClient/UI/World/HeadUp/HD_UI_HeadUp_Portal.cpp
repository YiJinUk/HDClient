// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HeadUp/HD_UI_HeadUp_Portal.h"

#include "Components/TextBlock.h"

void UHD_UI_HeadUp_Portal::UIPortalSetText(const FString& str_text)
{
	_text->SetText(FText::FromString(str_text));
}