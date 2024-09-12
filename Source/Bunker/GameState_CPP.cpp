// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState_CPP.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AGameState_CPP::OnRep_PlayerDataUpdate()
{
	OnPlayerDataChanged();
}

void AGameState_CPP::OnRep_ChatMessages()
{
	OnChatMessagesChanged();
}

TArray<UPlayerData*> AGameState_CPP::GetPlayerData(UObject* WorldContextObject)
{
	return GetGameStateCPP(WorldContextObject)->PlayerDataArray;
}

TArray<FChatMessage> AGameState_CPP::GetChatLog(UObject* WorldContextObject)
{
	return  GetGameStateCPP(WorldContextObject)->ChatMessages;
}

AGameState_CPP* AGameState_CPP::GetGameStateCPP(UObject* WorldContextObject)
{
	return Cast<AGameState_CPP>( UGameplayStatics::GetGameState(WorldContextObject));
}

void AGameState_CPP::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGameState_CPP, ChatMessages);
	DOREPLIFETIME(AGameState_CPP, PlayerDataArray);
}



// Constructor definition
UPlayerData::UPlayerData()
{

	FPlayerProperty DefaultProperty(FText::FromString(TEXT("Значение не задано")), FText::FromString(TEXT("")), 1);

	PropertiesMap.Add(EPropertyCategory::Name, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Sex, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Age, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Job, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Health, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Hobby, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Knowledge, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Luggage, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Personality, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::Phobia, DefaultProperty);
	PropertiesMap.Add(EPropertyCategory::OtherInfo, DefaultProperty);
}

// Getter implementation
inline FPlayerProperty UPlayerData::GetProperty(EPropertyCategory PropertyKey) const
{
	// Check if the key exists in the map before attempting to access it
	if (const FPlayerProperty* Property = PropertiesMap.Find(PropertyKey))
	{
		return *Property;  // Return the found property
	}

	// Return a default property if the key does not exist
	return FPlayerProperty(FText::FromString(TEXT("Not Found")), FText::FromString(TEXT("")), 0);
}

// Setter implementation
inline void UPlayerData::SetProperty(EPropertyCategory PropertyKey, const FPlayerProperty& PropertyValue, UObject* ContextObject )
{
	// Set or update the property in the map
	PropertiesMap.Add(PropertyKey, PropertyValue);

	
	ContextObject->GetWorld()->GetGameState()->ForceNetUpdate();
	
}
void UPlayerData::SetID(const FString& NewID, UObject* ContextObject)
{
	if (ID != NewID)
	{
		ID = NewID;
		ContextObject->GetWorld()->GetGameState()->ForceNetUpdate();
	}
}

// Implementation of SetIsConnected
void UPlayerData::SetIsConnected(bool NewIsConnected, UObject* ContextObject)
{
	if (IsConnected != NewIsConnected)
	{
		IsConnected = NewIsConnected;
		ContextObject->GetWorld()->GetGameState()->ForceNetUpdate();
	}
}

void UPlayerData::SetPlayerIDAndConnection(const FString& NewID, bool NewIsConnected, UObject* ContextObject)
{
	
	this->IsConnected = NewIsConnected;
	this->ID = NewID;
	ContextObject->GetWorld()->GetGameState()->ForceNetUpdate();
	
}
