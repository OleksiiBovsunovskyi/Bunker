// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
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
struct FPropertyCategoryPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPropertyCategory Category;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsUnlocked;

	// Constructor for convenience
	FPropertyCategoryPair()
		: Category(EPropertyCategory::Sex), bIsUnlocked(false) {}

	FPropertyCategoryPair(EPropertyCategory InCategory, bool bInIsUnlocked)
		: Category(InCategory), bIsUnlocked(bInIsUnlocked) {}
};
USTRUCT(BlueprintType)
struct FPropertyOverwrite
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPropertyCategory Category;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerProperty NewProperty;

};

USTRUCT(BlueprintType)
struct FPlayerData
{	
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FPropertyOverwrite> PropertyOverwrites;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FPropertyCategoryPair> UnlockedProp =
	{
		FPropertyCategoryPair(EPropertyCategory::Sex, false),
		FPropertyCategoryPair(EPropertyCategory::Age, false),
		FPropertyCategoryPair(EPropertyCategory::Job, false),
		FPropertyCategoryPair(EPropertyCategory::Health, false),
		FPropertyCategoryPair(EPropertyCategory::Hobby, false),
		FPropertyCategoryPair(EPropertyCategory::Knowledge, false),
		FPropertyCategoryPair(EPropertyCategory::Luggage, false),
		FPropertyCategoryPair(EPropertyCategory::Personality, false),
		FPropertyCategoryPair(EPropertyCategory::Phobia, false),
		FPropertyCategoryPair(EPropertyCategory::OtherInfo, false)
	};
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

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void OverWriteProperty(FString ID, FPropertyOverwrite Overwrite, UObject* WorldContextObject)
	{
		TArray<FPlayerData>& PlayerDataArray = GetGameStateCPP(WorldContextObject)->PlayerDataArray;

		for(int i = 0; i < PlayerDataArray.Num(); i++)
		{
			if(PlayerDataArray[i].ID == ID)
			{
				for(int j = 0; j < PlayerDataArray[i].PropertyOverwrites.Num(); j++)
				{
					if(PlayerDataArray[i].PropertyOverwrites[j].Category == Overwrite.Category)
					{
						PlayerDataArray[i].PropertyOverwrites.RemoveAt(j);
					}
				}
				PlayerDataArray[i].PropertyOverwrites.Add(Overwrite);
				GetGameStateCPP(WorldContextObject)->ForceNetUpdate();
				GetGameStateCPP(WorldContextObject)->OnRep_PlayerDataUpdate();
				return;
			}
		}
	}
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static bool SetIsConnectedByID(FString ID, bool NewIsConnected, UObject* WorldContextObject)
	{
		TArray<FPlayerData>& ARR = GetGameStateCPP(WorldContextObject)->PlayerDataArray;
		for (int j = 0; j < ARR.Num(); j++) {
			
			if (ARR[j].ID == ID) {
				ARR[j].IsConnected = NewIsConnected;
				GetGameStateCPP(WorldContextObject)->ForceNetUpdate();  // Force replication update
				GetGameStateCPP(WorldContextObject)->OnRep_PlayerDataUpdate();
				return true;
			}
		}
		return false;

	}
		
	UFUNCTION(BlueprintCallable)
	void SetIsConnected(UPARAM(ref) FPlayerData& Data, bool NewIsConnected)
	{
		if(!HasAuthority() ) UE_LOG(LogTemp, Warning, TEXT("Tried to modify IsConnected from client, call this only on server"));
		
		Data.IsConnected = NewIsConnected;
		OnRep_PlayerDataUpdate();
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetIsUnlocked(UPARAM(ref) FPlayerData& Data, EPropertyCategory Prop)
	{
		for (FPropertyCategoryPair& Pair : Data.UnlockedProp)
		{
			if (Pair.Category == Prop)
			{
				return Pair.bIsUnlocked;
			}
		}
		return false;
	}

	UFUNCTION(BlueprintCallable)
	void SetUnlockedProperty(UPARAM(ref) FPlayerData& Data, EPropertyCategory Prop, bool IsUnlocked = true)
	{
	//if (!HasAuthority())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Tried to modify IsUnlocked from client, call this only on server"));
	//	return;
	//}

		// Find and update the property in the array
		for (FPropertyCategoryPair& Pair : Data.UnlockedProp)
		{
			if (Pair.Category == Prop)
			{
				Pair.bIsUnlocked = IsUnlocked;
				ForceNetUpdate();  // Force replication update
				OnRep_PlayerDataUpdate();
				return;
			}
		}

		// If not found, log a warning (this shouldn't happen unless the array is modified elsewhere)
		UE_LOG(LogTemp, Warning, TEXT("Property not found in UnlockedProp array!"));
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
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void GetPlayerDataByID(UObject*WorldContextObject, FString ID, FPlayerData& DataOut)
	{
		TArray<FPlayerData>& PlayerDataArray = GetGameStateCPP(WorldContextObject)->PlayerDataArray;
		for(int i = 0; i < PlayerDataArray.Num(); i++)
		{
			if(PlayerDataArray[i].ID == ID)
				DataOut = PlayerDataArray[i];
		}
	}

	
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FPlayerProperty GetPropertyOverWrite(UObject*WorldContextObject, FString ID, EPropertyCategory Category)
	{
		FPlayerData PlayerData;
		GetPlayerDataByID(WorldContextObject, ID, PlayerData);

		for(auto i : PlayerData.PropertyOverwrites)
		{
			if(i.Category == Category)
				return i.NewProperty;
		}
		return FPlayerProperty();
	}
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FPlayerProperty GeneratePlayerProperty(UObject*WorldContextObject, EPropertyCategory PropertyCategory, int RoomSeed,
		FString PlayerID, int AgeMin = 16, int AgeMax = 80)
	{
		FPlayerData PlayerData;
		GetPlayerDataByID(WorldContextObject, PlayerID, PlayerData);
		int LocalSeed = PlayerData.LocalGenSeed;
		FPlayerProperty Prop = GetPropertyOverWrite(WorldContextObject, PlayerID, PropertyCategory);
		if( !Prop.Property.IsEmpty())
			return  Prop;
	
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
