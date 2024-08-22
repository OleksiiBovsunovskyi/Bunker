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
	static TArray<FPlayerProperty> SexOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetSexOptions(){return  SexOptions;}

	static TArray<FPlayerProperty> JobOptions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FPlayerProperty> GetJobOptions(){return  JobOptions;}
	
};
