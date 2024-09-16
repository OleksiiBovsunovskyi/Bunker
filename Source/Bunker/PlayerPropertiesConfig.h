// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <random>
#include "Chaos/Tetrahedron.h"
#include "PlayerPropertiesConfig.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerProperty
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GenChance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Property;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;
	FPlayerProperty();
	FPlayerProperty(const FText& property, const FText& description, float genChance = 1	);
};

UENUM(BlueprintType)
enum class EPropertyCategory : uint8
{
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
class BUNKER_API UPlayerPropertiesConfig : public UObject
{
	GENERATED_BODY()
public:


	static TMap<EPropertyCategory, TArray<FPlayerProperty>> PropertiesList;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FPlayerProperty GetPropertyBySeed(int Seed, EPropertyCategory Category)
	{
		std::mt19937 mt(GetTypeHash(Seed) + static_cast<int>(Category));
		
		std::uniform_int_distribution<int> dist(0, PropertiesList[Category].Num()-1);
		int Indx = dist(mt);
		return PropertiesList[Category][Indx];
	}
	
};
