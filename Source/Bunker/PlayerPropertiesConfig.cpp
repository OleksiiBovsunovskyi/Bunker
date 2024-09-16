// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPropertiesConfig.h"
#include "Internationalization/TextTransformer.h" 
#define LOCTEXT_NAMESPACE "Player data"

#include "PlayerPropertiesConfig.h"

// Static const initialization in the cpp file
TMap<EPropertyCategory, TArray<FPlayerProperty>> UPlayerPropertiesConfig::PropertiesList =
{
    { EPropertyCategory::Sex, {
        FPlayerProperty(FText::FromString(TEXT("Мужчина")), FText::FromString(TEXT("Мужчина")), 1),
        FPlayerProperty(FText::FromString(TEXT("Женщина")), FText::FromString(TEXT("Женщина")), 1)
    }},


    { EPropertyCategory::Job, {
        FPlayerProperty(FText::FromString(TEXT("Doctor")), FText::FromString(TEXT("Medical professional")), 0.2f),
        FPlayerProperty(FText::FromString(TEXT("Engineer")), FText::FromString(TEXT("Technical professional")), 0.3f),
        FPlayerProperty(FText::FromString(TEXT("Artist")), FText::FromString(TEXT("Creative professional")), 0.1f)
    }},

    { EPropertyCategory::Health, {
        FPlayerProperty(FText::FromString(TEXT("Healthy")), FText::FromString(TEXT("No known medical conditions")), 0.7f),
        FPlayerProperty(FText::FromString(TEXT("Diabetic")), FText::FromString(TEXT("Chronic medical condition")), 0.2f),
        FPlayerProperty(FText::FromString(TEXT("Asthmatic")), FText::FromString(TEXT("Respiratory condition")), 0.1f)
    }},

    { EPropertyCategory::Hobby, {
        FPlayerProperty(FText::FromString(TEXT("Reading")), FText::FromString(TEXT("Enjoys reading books")), 0.4f),
        FPlayerProperty(FText::FromString(TEXT("Traveling")), FText::FromString(TEXT("Enjoys traveling")), 0.3f),
        FPlayerProperty(FText::FromString(TEXT("Cooking")), FText::FromString(TEXT("Loves experimenting with food")), 0.3f)
    }},

    { EPropertyCategory::Knowledge, {
        FPlayerProperty(FText::FromString(TEXT("Physics")), FText::FromString(TEXT("Expert in physics")), 0.3f),
        FPlayerProperty(FText::FromString(TEXT("Mathematics")), FText::FromString(TEXT("Skilled in mathematics")), 0.5f),
        FPlayerProperty(FText::FromString(TEXT("History")), FText::FromString(TEXT("Has a deep knowledge of history")), 0.2f)
    }},

    { EPropertyCategory::Luggage, {
        FPlayerProperty(FText::FromString(TEXT("Backpack")), FText::FromString(TEXT("Carries a backpack")), 0.6f),
        FPlayerProperty(FText::FromString(TEXT("Suitcase")), FText::FromString(TEXT("Carries a suitcase")), 0.3f),
        FPlayerProperty(FText::FromString(TEXT("Duffel Bag")), FText::FromString(TEXT("Carries a duffel bag")), 0.1f)
    }},

    { EPropertyCategory::Personality, {
        FPlayerProperty(FText::FromString(TEXT("Outgoing")), FText::FromString(TEXT("Extroverted and social")), 0.4f),
        FPlayerProperty(FText::FromString(TEXT("Introverted")), FText::FromString(TEXT("Prefers solitude")), 0.3f),
        FPlayerProperty(FText::FromString(TEXT("Ambitious")), FText::FromString(TEXT("Driven and goal-oriented")), 0.3f)
    }},

    { EPropertyCategory::Phobia, {
        FPlayerProperty(FText::FromString(TEXT("Arachnophobia")), FText::FromString(TEXT("Fear of spiders")), 0.2f),
        FPlayerProperty(FText::FromString(TEXT("Acrophobia")), FText::FromString(TEXT("Fear of heights")), 0.3f),
        FPlayerProperty(FText::FromString(TEXT("Claustrophobia")), FText::FromString(TEXT("Fear of confined spaces")), 0.5f)
    }},

    { EPropertyCategory::OtherInfo, {
        FPlayerProperty(FText::FromString(TEXT("Vegetarian")), FText::FromString(TEXT("Follows a vegetarian diet")), 0.4f),
        FPlayerProperty(FText::FromString(TEXT("Non-Smoker")), FText::FromString(TEXT("Does not smoke")), 0.6f)
    }}
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
