// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState_CPP.h"

void AGameState_CPP::AddToChat(FChatMessage message)
{
	ChatLog.Add(message);
}

TArray<FChatMessage> AGameState_CPP::GetChatMessages()
 {
	return ChatLog;
 }
 