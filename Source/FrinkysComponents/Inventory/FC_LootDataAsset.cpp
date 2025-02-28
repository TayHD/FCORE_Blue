// Copyright Frinky 2022


#include "FC_LootDataAsset.h"

TSubclassOf<AActor> UFC_LootDataAsset::GetRandomItem()
{
	if(LootItems.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "No items in loot table, add some!");
		return nullptr;
	}
    
	// Create a temporary array to hold normalized probabilities
	TArray<FLootItemStruct> TempLootItems = LootItems;

	// Calculate the total probability of all items
	float TotalProbability = 0.0f;
	for (const FLootItemStruct& Item : TempLootItems)
	{
		TotalProbability += Item.SpawnProbability;
	}

	// Normalize the probabilities in the temporary array
	for (FLootItemStruct& Item : TempLootItems)
	{
		Item.SpawnProbability /= TotalProbability;
	}

	// Generate a random number between 0 and 1.0 (the total normalized probability)
	float RandomNumber = FMath::FRandRange(0.0f, 1.0f);
    
	// Loop through the items in the temporary array, now with normalized probabilities
	for (const FLootItemStruct& Item : TempLootItems)
	{
		RandomNumber -= Item.SpawnProbability;
		if (RandomNumber <= 0)
		{
			return Item.ItemClass;
		}
	}

	// If we get here, something is really broken
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Something went wrong with the loot table");
	return nullptr;
}

