// Nathaniel Richards 2021


#include "PResourceSpawner.h"

APResourceSpawner::APResourceSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Slot1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot1"));
	Slot1Spawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot1Spawn"));


	Slot2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot2"));
	Slot2Spawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot2Spawn"));


	Slot3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot3"));
	Slot3Spawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot3Spawn"));
}

void APResourceSpawner::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

void APResourceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APResourceSpawner::Spawn()
{
	FString Slot1Randomized = GetResourceType(rand() % 7);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Slot1Randomized);
}

FString APResourceSpawner::GetResourceType(int32 Index)
{
	TArray<FString> ResourceTypes =
	{
		"Silver",
		"Bronze",
		"Copper",
		"Iron",
		"Gold",
		"Platinum",
		"Diamond"
	};
	return ResourceTypes[Index];
}
