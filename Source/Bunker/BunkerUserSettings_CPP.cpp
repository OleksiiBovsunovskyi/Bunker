// Fill out your copyright notice in the Description page of Project Settings.


#include "BunkerUserSettings_CPP.h"

FString UBunkerUserSettings_CPP::GetUserNickName()
{
	return UserNickName;
}

void UBunkerUserSettings_CPP::SetUserNickName(FString NewUserNickName)
{
	UserNickName = NewUserNickName;
}

float UBunkerUserSettings_CPP::GetMouseSensitivity() const
{
	return MouseSensitivity;
}

void UBunkerUserSettings_CPP::SetMouseSensitivity(float NewSensitivity)
{
	MouseSensitivity = NewSensitivity;
	
}


