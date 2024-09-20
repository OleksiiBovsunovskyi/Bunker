// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerPropertiesConfig.h"
#include "PropertiesGeneration.generated.h"


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
class BUNKER_API UPropertiesGeneration : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION()
	static FPlayerProperty GetRandomPlayerProperty(const TArray<FPlayerProperty>& Source, const FRandomStream& RandomStream);


	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FPlayerProperty GetPropertyOverWrite(UObject*WorldContextObject, FString ID, EPropertyCategory Category);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void GetPlayerDataByID(UObject*WorldContextObject, FString ID, FPlayerData& DataOut);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FPlayerProperty GeneratePlayerProperty(UObject*WorldContextObject, EPropertyCategory PropertyCategory, int RoomSeed,
		FString PlayerID, int AgeMin = 16, int AgeMax = 80);
	UFUNCTION()
	static FPlayerProperty GenerateRandomAgeData(int RoomSeed, int LocalSeed, int Min = 16, int Max = 80);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void OverWriteProperty(FString ID, FPropertyOverwrite Overwrite, UObject* WorldContextObject);

};
