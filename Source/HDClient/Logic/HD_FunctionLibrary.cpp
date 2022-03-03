// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_FunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

float UHD_FunctionLibrary::GetDistance2DByVector(FVector2D v_loc_owner, FVector2D v_loc_target)
{
	return (v_loc_owner - v_loc_target).Size();
}
FVector2D UHD_FunctionLibrary::GetVelocity2DByV2(const FVector2D& v2_loc_start, const FVector2D& v2_loc_end)
{
	return (v2_loc_end - v2_loc_start).GetSafeNormal();
}
float UHD_FunctionLibrary::GetFindLookRotatorYawByV3(const FVector& v_owner, const FVector& v_target)
{
	return UKismetMathLibrary::FindLookAtRotation(v_owner, v_target).Yaw;
}
void UHD_FunctionLibrary::GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color)
{
	GEngine->AddOnScreenDebugMessage(i_key, f_time, s_color, str_message);
}
