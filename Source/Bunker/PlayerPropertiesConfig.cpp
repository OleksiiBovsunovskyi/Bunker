// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPropertiesConfig.h"
#include "Internationalization/TextTransformer.h" 
#define LOCTEXT_NAMESPACE "Player data"
TArray<FPlayerProperty> UPlayerPropertiesConfig::SexOptions
	{
		FPlayerProperty(FText::FromString(TEXT("Мужчина")), FText::FromString(TEXT("Мужчина")), 1),
		FPlayerProperty(FText::FromString(TEXT("Женщина")), FText::FromString(TEXT("Женщина")), 1)
	
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::JobOptions
	{
		FPlayerProperty(FText::FromString(L"Адвокат"), FText::FromString(L"Представляет интересы клиентов в суде и консультирует по юридическим вопросам."),1),
	FPlayerProperty(FText::FromString(L"Архитектор"), FText::FromString(L"Проектирует здания и сооружения, следя за их функциональностью и эстетикой."),1),
	FPlayerProperty(FText::FromString(L"Библиотекарь"), FText::FromString(L"Управляет библиотечными ресурсами и помогает посетителям находить информацию."),1)
	
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::AgeOptions
    {
    	FPlayerProperty(FText::FromString(L"20"), FText::FromString(L"Молодой"),1),
    	FPlayerProperty(FText::FromString(L"47"), FText::FromString(L"Взрослый"),0.5),
    	FPlayerProperty(FText::FromString(L"69"), FText::FromString(L"Пожилой"),0.2)
    };

TArray<FPlayerProperty> UPlayerPropertiesConfig::HealthOptions
    {
    	FPlayerProperty(FText::FromString(L"Идеальное здоровье"), FText::FromString(L""),0.4),
		FPlayerProperty(FText::FromString(L"Авитаминоз"), FText::FromString(L" Недостаток витаминов в организме, вызывающий различные симптомы и заболевания."), 0.2),
		FPlayerProperty(FText::FromString(L"Азооспермия"), FText::FromString(L"Отсутствие сперматозоидов в эякуляте, что приводит к мужскому бесплодию."),0.5)
    };

TArray<FPlayerProperty> UPlayerPropertiesConfig::HobbyOptions
	{
		FPlayerProperty(FText::FromString(L"Спортивные игры в команде"), FText::FromString(L""), 1),
		FPlayerProperty(FText::FromString(L"Йога"), FText::FromString(L""), 1),
		FPlayerProperty(FText::FromString(L"Езда на велосипед"), FText::FromString(L""), 1)
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::PhobiaOptions
	{
		FPlayerProperty(FText::FromString(L"Авиафобия"), FText::FromString(L"Боязнь полётов в воздушных транспортных средствах"), 1),
		FPlayerProperty(FText::FromString(L"Агирофобия"), FText::FromString(L"Боязнь  улиц, пересекать улицу")),
		FPlayerProperty(FText::FromString(L"Агорафобия"), FText::FromString(L"Боязнь пространства, открытых мест, площадей, толп людей"))
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::PersonalityOptions
	{
		FPlayerProperty(FText::FromString(L"Агрессивный"), FText::FromString(L"")),
		FPlayerProperty(FText::FromString(L"Алчный"), FText::FromString(L"")),
		FPlayerProperty(FText::FromString(L"Альтруист"), FText::FromString(L""))
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::KnowledgeOptions
	{
		FPlayerProperty(FText::FromString(L"Лично знаком с президентом страны"), FText::FromString(L"")),
		FPlayerProperty(FText::FromString(L"Однажды выиграл миллион в лотерею"), FText::FromString(L"")),
		FPlayerProperty(FText::FromString(L"Знает каждый уголок этой местности, проводил здесь каждое лето с детства"), FText::FromString(L""))
	};

TArray<FPlayerProperty> UPlayerPropertiesConfig::LuggageOptions
	{
		FPlayerProperty(FText::FromString(L"Коробка спичек 5шт"), FText::FromString(L"")),
		FPlayerProperty(FText::FromString(L"Охотничье ружье и патроны"), FText::FromString(L"")),
		FPlayerProperty(FText::FromString(L"Снайперская винтовка"), FText::FromString(L""))
	};


#undef LOCTEXT_NAMESPACE 
FPlayerProperty::FPlayerProperty()
{
}

FPlayerProperty::FPlayerProperty(const FText& property, const FText& description, float genChance)
{
	Property = property;
	Description = description;
	GenChance = genChance;
}
