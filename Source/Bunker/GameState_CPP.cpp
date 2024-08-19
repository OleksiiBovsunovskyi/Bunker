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
