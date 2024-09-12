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


UENUM(BlueprintType)
enum class EPropertyCategory : uint8
{
	Name		UMETA(DisplayName = "Name"),         // Name property
	Sex         UMETA(DisplayName = "Sex"),          // Sex property
	Age         UMETA(DisplayName = "Age"),          // Age property
	Job         UMETA(DisplayName = "Job"),          // Job property
	Health      UMETA(DisplayName = "Health"),       // Health property
	Hobby       UMETA(DisplayName = "Hobby"),        // Hobby property
	Knowledge   UMETA(DisplayName = "Knowledge"),    // Knowledge property
	Luggage     UMETA(DisplayName = "Luggage"),      // Luggage property
	Personality UMETA(DisplayName = "Personality"),  // Personality property
	Phobia      UMETA(DisplayName = "Phobia"),       // Phobia property
	OtherInfo   UMETA(DisplayName = "Other Info")    // Other Info property
   
};
UCLASS(BlueprintType)
class BUNKER_API UPlayerData : public UObject
{
    GENERATED_BODY()

public:
    // Default constructor
    UPlayerData();

    // Property map with EPropertyCategory as key and FPlayerProperty as value
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Data")
    TMap<EPropertyCategory, FPlayerProperty> PropertiesMap;

    // Player ID
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Data")
    FString ID;

    // Player connection status
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Data")
    bool IsConnected;

    // Getter for property by key
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data")
    FPlayerProperty GetProperty(EPropertyCategory PropertyKey) const;

	// Setter for property by key with context object defaulted to self
	UFUNCTION(BlueprintCallable, Category = "Player Data", meta = (DefaultToSelf = "ContextObject"))
	void SetProperty(EPropertyCategory PropertyKey, const FPlayerProperty& PropertyValue, UObject* ContextObject = nullptr);

	// Setter for ID with context object defaulted to self
	UFUNCTION(BlueprintCallable, Category = "Player Data", meta = (DefaultToSelf = "ContextObject"))
	void SetID(const FString& NewID, UObject* ContextObject = nullptr);

	// Setter for IsConnected with context object defaulted to self
	UFUNCTION(BlueprintCallable, Category = "Player Data", meta = (DefaultToSelf = "ContextObject"))
	void SetIsConnected(bool NewIsConnected, UObject* ContextObject = nullptr);

	// Combined setter for ID and IsConnected with context object defaulted to self
	UFUNCTION(BlueprintCallable, Category = "Player Data", meta = (DefaultToSelf = "ContextObject"))
	void SetPlayerIDAndConnection(const FString& NewID, bool NewIsConnected = true, UObject* ContextObject = nullptr);
};




UCLASS()
class BUNKER_API AGameState_CPP : public AGameState
{
	GENERATED_BODY()
public:
	
	UPROPERTY( BlueprintReadWrite, ReplicatedUsing=OnRep_ChatMessages	)
	TArray<FChatMessage> ChatMessages;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Player Data", ReplicatedUsing=OnRep_PlayerDataUpdate	)
	TArray<UPlayerData*> PlayerDataArray;

	UFUNCTION()
	void OnRep_PlayerDataUpdate();
	UFUNCTION()
	void OnRep_ChatMessages();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TArray<UPlayerData*> GetPlayerData(UObject* WorldContextObject);
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
	
	UFUNCTION(BlueprintCallable,  meta = (WorldContext = "WorldContextObject"))
	static UPlayerData* GeneratePlayerData(int RandomSeed, UObject* WorldContextObject)
	{
		// Initialize the random stream
		FRandomStream RandomStream(RandomSeed);

		// Create a new instance of UPlayerData
		UPlayerData* Data = NewObject<UPlayerData>();

		// Set the 'Sex' property
		FPlayerProperty SexProperty = GetRandomPlayerProperty(UPlayerPropertiesConfig::SexOptions, RandomStream);
		Data->SetProperty(EPropertyCategory::Sex, SexProperty, WorldContextObject);

		// Set the 'Job' property
		FPlayerProperty JobProperty = GetRandomPlayerProperty(UPlayerPropertiesConfig::JobOptions, RandomStream);
		Data->SetProperty(EPropertyCategory::Job, JobProperty, WorldContextObject);

		// Set the 'Age' property based on the 'Sex' property
		FPlayerProperty AgeProperty;
		if (SexProperty.Property.ToString() == UPlayerPropertiesConfig::SexOptions[0].Property.ToString())
		{
			AgeProperty = GenerateRandomAgeData(18, 78);
		}
		else
		{
			AgeProperty = GenerateRandomAgeData(18, 82);
		}
		Data->SetProperty(EPropertyCategory::Age, AgeProperty);

		// Set the remaining properties using the setters
		Data->SetProperty(EPropertyCategory::Health, GetRandomPlayerProperty(UPlayerPropertiesConfig::HealthOptions, RandomStream));
		Data->SetProperty(EPropertyCategory::Hobby, GetRandomPlayerProperty(UPlayerPropertiesConfig::HobbyOptions, RandomStream));
		Data->SetProperty(EPropertyCategory::Knowledge, GetRandomPlayerProperty(UPlayerPropertiesConfig::KnowledgeOptions, RandomStream));
		Data->SetProperty(EPropertyCategory::Luggage, GetRandomPlayerProperty(UPlayerPropertiesConfig::LuggageOptions, RandomStream));
		Data->SetProperty(EPropertyCategory::Personality, GetRandomPlayerProperty(UPlayerPropertiesConfig::PersonalityOptions, RandomStream));
		Data->SetProperty(EPropertyCategory::Phobia, GetRandomPlayerProperty(UPlayerPropertiesConfig::PhobiaOptions, RandomStream));

		// Return the populated UPlayerData instance
		return Data;
	}

};
