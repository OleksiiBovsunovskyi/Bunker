// Fill out your copyright notice in the Description page of Project Settings.

#include "GameState_CPP.h"
#include "PropertiesGeneration.h"

FPlayerProperty UPropertiesGeneration::GetRandomPlayerProperty(const TArray<FPlayerProperty>& Source,
	const FRandomStream& RandomStream)
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

FPlayerProperty UPropertiesGeneration::GetPropertyOverWrite(UObject* WorldContextObject, FString ID,
                                                            EPropertyCategory Category)
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

void UPropertiesGeneration::GetPlayerDataByID(UObject* WorldContextObject, FString ID, FPlayerData& DataOut)
{
	TArray<FPlayerData>& PlayerDataArray = AGameState_CPP::GetGameStateCPP(WorldContextObject)->PlayerDataArray;
	for(int i = 0; i < PlayerDataArray.Num(); i++)
	{
		if(PlayerDataArray[i].ID == ID)
			DataOut = PlayerDataArray[i];
	}
}
FPlayerProperty UPropertiesGeneration::GeneratePlayerProperty(UObject* WorldContextObject, EPropertyCategory PropertyCategory,
	int RoomSeed, FString PlayerID, int AgeMin, int AgeMax)
{
	FPlayerData PlayerData;
	UPropertiesGeneration::GetPlayerDataByID(WorldContextObject, PlayerID, PlayerData);
	int LocalSeed = PlayerData.LocalGenSeed;
	FPlayerProperty Prop = UPropertiesGeneration::GetPropertyOverWrite(WorldContextObject, PlayerID, PropertyCategory);
	if( !Prop.Property.IsEmpty())
		return  Prop;
	
	int Seed = (RoomSeed/2)+(LocalSeed/2);
		
	FMath::RandInit(Seed);
	//Age is generated as random number, it is not chosen from config array
	if(PropertyCategory == EPropertyCategory::Age)
		return GenerateRandomAgeData(RoomSeed, LocalSeed, AgeMin, AgeMax);
	return UPlayerPropertiesConfig::GetPropertyBySeed(Seed, PropertyCategory);
		
}

FPlayerProperty  UPropertiesGeneration::GenerateRandomAgeData(int RoomSeed, int LocalSeed, int Min, int Max)
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

void UPropertiesGeneration::OverWriteProperty(FString ID, FPropertyOverwrite Overwrite, UObject* WorldContextObject)
{
	AGameState_CPP* GameState = AGameState_CPP::GetGameStateCPP(WorldContextObject);
	TArray<FPlayerData>& PlayerDataArray = GameState->PlayerDataArray;

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
			GameState->ForceNetUpdate();
			GameState->OnRep_PlayerDataUpdate();
			return;
		}
	}
}