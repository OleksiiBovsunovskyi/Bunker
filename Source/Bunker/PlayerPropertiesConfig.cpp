// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPropertiesConfig.h"
#include "Internationalization/TextTransformer.h" 
#define LOCTEXT_NAMESPACE "Player data"
TArray<FPlayerProperty> UPlayerPropertiesConfig::SexOptions
	{
		FPlayerProperty(FText::FromString(TEXT("Мужчина")), FText::FromString(TEXT("Мужчина"))),
		FPlayerProperty(FText::FromString(TEXT("Женщина")), FText::FromString(TEXT("Женщина"))),
	
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::JobOptions
	{
		FPlayerProperty(FText::FromString(L"Адвокат"), FText::FromString(L"Представляет интересы клиентов в суде и консультирует по юридическим вопросам.")),
	FPlayerProperty(FText::FromString(L"Архитектор"), FText::FromString(L"Проектирует здания и сооружения, следя за их функциональностью и эстетикой.")),
	FPlayerProperty(FText::FromString(L"Библиотекарь"), FText::FromString(L"Управляет библиотечными ресурсами и помогает посетителям находить информацию."))
	
	};

#undef LOCTEXT_NAMESPACE 
FPlayerProperty::FPlayerProperty()
{
}

FPlayerProperty::FPlayerProperty(const FText& property, const FText& description)
{
	Property = property;
	Description = description;
}
