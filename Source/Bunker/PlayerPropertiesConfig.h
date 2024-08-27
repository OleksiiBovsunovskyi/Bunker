// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FText Property;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;
	FPlayerProperty();
	FPlayerProperty(const FText& property, const FText& description		);
};
UCLASS(BlueprintType)
class BUNKER_API UPlayerPropertiesConfig : public UObject
{
	GENERATED_BODY()
public:
	//  SEX
	static TArray<FPlayerProperty> SexOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetSexOptions(){return  SexOptions;}
	// SEX
	// JOB
	static TArray<FPlayerProperty> JobOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetJobOptions(){return  JobOptions;}
    // JOB
	// AGE
	static TArray<FPlayerProperty> AgeOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetAgeOptions(){return  AgeOptions;}
	// AGE
	// HEALTH
	static TArray<FPlayerProperty> HealthOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetHealthOptions(){return  HealthOptions;}
	// HEALTH
	// HOBBY
	static TArray<FPlayerProperty> HobbyOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetHobbyOptions(){return  HobbyOptions;}
	// HOBBY
	// PHOBIA
	static TArray<FPlayerProperty> PhobiaOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetPhobiaOptions(){return  PhobiaOptions;}
	// PHOBIA
	// PERSONALITY
	static TArray<FPlayerProperty> PersonalityOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetPersonalityOptions(){return  PersonalityOptions;}
	// PERSONALITY
	// KNOWLEDGE
	static TArray<FPlayerProperty> KnowledgeOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetKnowledgeOptions(){return  KnowledgeOptions;}
	// KNOWLEDGE
	// LUGGAGE
	static TArray<FPlayerProperty> LuggageOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetLuggageOptions(){return  LuggageOptions;}
	// LUGGAGE
	//FURTHER INFORMATION
	static TArray<FPlayerProperty> FurtherInformationOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetFurtherInformationOptions(){return  FurtherInformationOptions;}
	//FURTHER INFORMATION
	


};
