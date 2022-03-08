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

void UHD_FunctionLibrary::GSaveLog(FString s_log, FString s_filename, bool b_is_overwriting)
{
	//static int i_num = 0;
	//FString s_num = FString::FromInt(++i_num);

	//FString s_save_directory = FPaths::ProjectUserDir() + "/Logs";//FString("D:/TextLogs");
	//FString s_tmp_log = s_num + " '" + s_log + "'\n";


	//IPlatformFile& obj_platform_file = FPlatformFileManager::Get().GetPlatformFile();

	//if (obj_platform_file.CreateDirectoryTree(*s_save_directory))
	//{
	//	IFileManager* obj_file_manager;
	//	FString s_filepath = s_save_directory + "/" + s_filename;
	//	if (b_is_overwriting)
	//		FFileHelper::SaveStringToFile(s_tmp_log, *s_filepath);
	//	else
	//		FFileHelper::SaveStringToFile(s_tmp_log, *s_filepath, FFileHelper::EEncodingOptions::AutoDetect, &obj_file_manager->Get(), FILEWRITE_Append);
	//}
}
void UHD_FunctionLibrary::GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color)
{
	GEngine->AddOnScreenDebugMessage(i_key, f_time, s_color, str_message);
}
