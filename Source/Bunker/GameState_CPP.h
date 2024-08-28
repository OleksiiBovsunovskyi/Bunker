// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerPropertiesConfig.h"
#include "GameState_CPP.generated.h"

/**
 * 
 
 */

USTRUCT(BlueprintType)
struct FChatMessage
{	
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Message;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Author;
	
};



USTRUCT(BlueprintType)
struct FPlayerData
{	
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Sex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Job;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Age;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Hobby;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Knowledge;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Luggage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Personality;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty Phobia;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty OtherInfo;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsConnected;

	

};

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
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnChatMessagesChanged();
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDataChanged();

	UFUNCTION()
	static FPlayerProperty GenerateRandomAgeData(int Min = 16, int Max = 80)
	{
		FPlayerProperty AgeData;
		//Set random seed to ensure new result each time
		FMath::RandInit(FDateTime::Now().GetTicks());
		// Generate a random age between Min and Max
		int32 RandomAge = FMath::RandRange(Min, Max);
    
		// Determine the age category
		FString AgeCategory;
		if (RandomAge <= 25)
		{
			AgeCategory = L"Молодой";
		}
		else if (RandomAge <= 60)
		{
			AgeCategory = L"Взрослый";
		}
		else
		{
			AgeCategory = L"Пожилой";
		}
    
		// Format the result as FText
		AgeData.Property = FText::FromString(FString::Printf(TEXT("%d (%s)"), RandomAge, *AgeCategory));
    
		return AgeData;
	}
	
	UFUNCTION(BlueprintCallable)
	static FPlayerData GeneratePlayerData(int RandomSeed)
	{
		FRandomStream RandomStream(RandomSeed);
		FPlayerData Data;
		
		Data.Sex = UPlayerPropertiesConfig::SexOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::SexOptions.Num() - 1)];
		Data.Job = UPlayerPropertiesConfig::JobOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::JobOptions.Num() - 1)];
		if(Data.Sex.Property.ToString() == UPlayerPropertiesConfig::SexOptions[0].Property.ToString())
			Data.Age = GenerateRandomAgeData(18, 78);
		else Data.Age = GenerateRandomAgeData(18, 82);
		Data.Health = UPlayerPropertiesConfig::HealthOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::HealthOptions.Num() - 1)];
		Data.Hobby = UPlayerPropertiesConfig::HobbyOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::HobbyOptions.Num() - 1)];
		Data.Knowledge = UPlayerPropertiesConfig::KnowledgeOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::KnowledgeOptions.Num() - 1)];
		Data.Luggage = UPlayerPropertiesConfig::LuggageOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::LuggageOptions.Num() - 1)];
		Data.Personality = UPlayerPropertiesConfig::PersonalityOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::PersonalityOptions.Num() - 1)];
		Data.Phobia = UPlayerPropertiesConfig::PhobiaOptions[RandomStream.RandRange(0, UPlayerPropertiesConfig::PhobiaOptions.Num() - 1)];

		return Data;
	}

};
