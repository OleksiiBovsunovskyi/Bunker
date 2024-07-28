// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "BunkerUserSettings_CPP.generated.h"

/**
 * 
 */
UCLASS()
class BUNKER_API UBunkerUserSettings_CPP : public UGameUserSettings
{
	GENERATED_BODY()
private:
	UPROPERTY(Config)
	FString UserNickName;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetUserNickName();
	UFUNCTION(BlueprintCallable)
	void SetUserNickName(FString NewUserNickName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UBunkerUserSettings_CPP* GetBunkerUserSettings_CPP()
	{
		return Cast<UBunkerUserSettings_CPP>(GetGameUserSettings());
	}
};
