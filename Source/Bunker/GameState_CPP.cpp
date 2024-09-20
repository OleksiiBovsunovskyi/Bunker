// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState_CPP.h"

#include "Kismet/GameplayStatics.h"
#include "PropertiesGeneration.h"
#include "Net/UnrealNetwork.h"

void AGameState_CPP::OnRep_PlayerDataUpdate()
{
	OnPlayerDataChanged();
}

void AGameState_CPP::OnRep_ChatMessages()
{
	OnChatMessagesChanged();
}

TArray<FPlayerData> AGameState_CPP::GetPlayerData(UObject* WorldContextObject)
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


bool AGameState_CPP::SetIsConnectedByID(FString ID, bool NewIsConnected, UObject* WorldContextObject)
{
	AGameState_CPP* GameState = GetGameStateCPP(WorldContextObject);
	TArray<FPlayerData>& ARR = GameState->PlayerDataArray;
	for (int j = 0; j < ARR.Num(); j++) {
			
		if (ARR[j].ID == ID) {
			ARR[j].IsConnected = NewIsConnected;
			GameState->ForceNetUpdate();  // Force replication update
			GameState->OnRep_PlayerDataUpdate();
			return true;
		}
	}
	return false;

}

void AGameState_CPP::SetIsConnected(FPlayerData& Data, bool NewIsConnected)
{
	if(!HasAuthority() ) UE_LOG(LogTemp, Warning, TEXT("Tried to modify IsConnected from client, call this only on server"));
		
	Data.IsConnected = NewIsConnected;
	OnRep_PlayerDataUpdate();
}

bool AGameState_CPP::GetIsUnlocked(FPlayerData& Data, EPropertyCategory Prop)
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

void AGameState_CPP::SetUnlockedProperty(FPlayerData& Data, EPropertyCategory Prop, bool IsUnlocked)
{
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



int32 AGameState_CPP::GetSeedFromNickname(const FString& Nickname)
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
