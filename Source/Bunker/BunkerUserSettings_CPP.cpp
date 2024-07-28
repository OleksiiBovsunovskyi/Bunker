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
