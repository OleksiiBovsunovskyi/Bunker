// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/SecureHash.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerPropertiesConfig.h"
#include "Iris/ReplicationState/ReplicationStateUtil.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int LocalGenSeed;
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
	void SetIsConnected(UPARAM(ref) FPlayerData& Data, bool NewIsConnected)
	{
		if(!HasAuthority() ) UE_LOG(LogTemp, Warning, TEXT("Tried to modify IsConnected from client, call this only on server"));
		
		Data.IsConnected = NewIsConnected;
		OnRep_PlayerDataUpdate();
	}
	UFUNCTION()
	static FPlayerProperty GetRandomPlayerProperty(const TArray<FPlayerProperty>& Source, const FRandomStream& RandomStream)
	{
		//FRandomStream RandomStream(RandomSeed);
		FPlayerProperty Prop;
		bool bValidProperty = false;
		
		while (!bValidProperty)
		{
			Prop = Source[RandomStream.RandRange(0, Source.Num() - 1)];
			bValidProperty = (RandomStream.RandRange(0, 100) / 100.0f) <= Prop.GenChance;
		}

		return Prop;
	}

	
	UFUNCTION(BlueprintCallable)
	static FPlayerProperty GeneratePlayerProperty(EPropertyCategory PropertyCategory, int RoomSeed, int LocalSeed, int AgeMin = 16, int AgeMax = 80)
	{
		FPlayerProperty Prop;
		int Seed = (RoomSeed/2)+(LocalSeed/2);
		FMath::RandInit(Seed);
		//Age is generated as random number, it is not chosen from config array
		if(PropertyCategory == EPropertyCategory::Age)
			return GenerateRandomAgeData(RoomSeed, LocalSeed, AgeMin, AgeMax);
		return UPlayerPropertiesConfig::GetPropertyBySeed(Seed, PropertyCategory);
		
	}
	UFUNCTION()
	static FPlayerProperty GenerateRandomAgeData(int RoomSeed, int LocalSeed, int Min = 16, int Max = 80)
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetSeedFromNickname(const FString& Nickname)
	{
		// Convert the nickname to a SHA-256 hash
		TArray<uint8> Data;
		Data.Append((uint8*)TCHAR_TO_ANSI(*Nickname), Nickname.Len());

		FSHAHash Hash;
		FSHA1::HashBuffer(Data.GetData(), Data.Num(), Hash.Hash);

		// Convert the hash to an integer seed
		int32 Seed = 0;
		for (int32 i = 0; i < Hash.ToString().Len(); ++i)
		{
			Seed += Hash.ToString()[i];
		}

		return Seed;
	}

	



};
