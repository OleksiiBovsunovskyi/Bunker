// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Misc/SecureHash.h"
#include "GameFramework/GameState.h"
#include "PlayerPropertiesConfig.h"
#include "PropertiesGeneration.h"
#include "GameState_CPP.generated.h"

UCLASS()
class BUNKER_API AGameState_CPP : public AGameState
{
	GENERATED_BODY()
public:
	
	UPROPERTY( BlueprintReadWrite, ReplicatedUsing=OnRep_ChatMessages	)
	TArray<FChatMessage> ChatMessages;

	UPROPERTY( BlueprintReadWrite, ReplicatedUsing=OnRep_PlayerDataUpdate	)
	TArray<FPlayerData> PlayerDataArray;

	UFUNCTION()
	void OnRep_PlayerDataUpdate();
	UFUNCTION()
	void OnRep_ChatMessages();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TArray<FPlayerData> GetPlayerData(UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TArray<FChatMessage> GetChatLog(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AGameState_CPP* GetGameStateCPP(UObject* WorldContextObject);
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnChatMessagesChanged();
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDataChanged();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void AddChatMessage(UObject* WorldContextObject, FChatMessage Message)
	{
		AGameState_CPP* GameState =  GetGameStateCPP(WorldContextObject);
		check(GameState);
		GameState->ChatMessages.Add(Message);		
	}

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static bool SetIsConnectedByID(FString ID, bool NewIsConnected, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void SetIsConnected(UPARAM(ref) FPlayerData& Data, bool NewIsConnected);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetIsUnlocked(UPARAM(ref) FPlayerData& Data, EPropertyCategory Prop);

	UFUNCTION(BlueprintCallable)
	void SetUnlockedProperty(UPARAM(ref) FPlayerData& Data, EPropertyCategory Prop, bool IsUnlocked = true);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetSeedFromNickname(const FString& Nickname);
};
