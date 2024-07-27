// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState_CPP.generated.h"

/**
 * 
 
 */

USTRUCT(BlueprintType)
struct FChatMessage
{
	GENERATED_BODY()
public:
	FString Message;
	FString Author;
	
};
 
UCLASS()
class BUNKER_API AGameState_CPP : public AGameState
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	TArray<FChatMessage> ChatLog;
	
	UFUNCTION(BlueprintCallable)
	void AddToChat(FChatMessage message);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FChatMessage> GetChatMessages();
	
	
};
