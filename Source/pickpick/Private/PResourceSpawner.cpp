// Nathaniel Richards 2021


#include "PResourceSpawner.h"

#include "PResourceSpawnable.h"

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

	BeginSpawn();
}

void APResourceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APResourceSpawner::GetCursorHit(FHitResult Hit)
{
	if (Hit.Component->GetName().Contains("Slot"))
	{
		FString NewName = Hit.Component->GetName();

		NewName.RemoveFromStart("Slot");

		ShowOption(FCString::Atoi(*NewName));

		PickedOption = FCString::Atoi(*NewName);
	}
}

void APResourceSpawner::GetCursorHitAndCollectResource(FHitResult Hit)
{
	if (HasRevealed && Hit.GetComponent() && Hit.GetActor())
	{
		if (Hit.GetActor()->GetClass()->IsChildOf(APResourceSpawnable::StaticClass()))
		{
			APResourceSpawnable* Spawnable = Cast<APResourceSpawnable>(Hit.GetActor());
			if (Spawnable->ResourceHealth >= 1.0f)
			{
				Spawnable->ResourceHealth -= 1.0f;
			}

			if (Spawnable->ResourceHealth <= 0.f)
			{
				Spawnable->Destroy();
				ShowUnpickedOptions();
			}
		}
	}
}

void APResourceSpawner::RouteCursorHit(FHitResult Hit)
{
	if (!Spawning)
	{
		if (!HasRevealed)
		{
			GetCursorHit(Hit);
		}
		else
		{
			GetCursorHitAndCollectResource(Hit);
		}
	}
}


void APResourceSpawner::BeginSpawn()
{
	Slot1->SetWorldLocation(Slot1Spawn->GetComponentLocation());
	Slot2->SetWorldLocation(Slot2Spawn->GetComponentLocation());
	Slot3->SetWorldLocation(Slot3Spawn->GetComponentLocation());

	PickedOption = -1;

	HasRevealed = false;
	Spawning = true;

	// wait spawn delay
	GetWorld()->GetTimerManager().SetTimer
	(
		SpawnDelayTimerHandle,
		this,
		&APResourceSpawner::Spawn,
		SpawnDelay,
		false
	);
}

void APResourceSpawner::Spawn()
{
	const FString Slot1Randomized = GetResourceType(rand() % 7);
	SetResourceForRandomizedSlot(Slot1Randomized, 1);

	const FString Slot2Randomized = GetResourceType(rand() % 7);
	SetResourceForRandomizedSlot(Slot2Randomized, 2);

	const FString Slot3Randomized = GetResourceType(rand() % 7);
	SetResourceForRandomizedSlot(Slot3Randomized, 3);

	Spawning = false;
}

void APResourceSpawner::ShowOption(int32 Index)
{
	HasRevealed = true;

	if (Index == 1)
	{
		FVector CurrentLocation = Slot1->GetComponentLocation();
		FVector NewLocation(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 120.f);
		Slot1->SetWorldLocation(NewLocation);
	}

	if (Index == 2)
	{
		FVector CurrentLocation = Slot2->GetComponentLocation();
		FVector NewLocation(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 120.f);
		Slot2->SetWorldLocation(NewLocation);
	}

	if (Index == 3)
	{
		FVector CurrentLocation = Slot3->GetComponentLocation();
		FVector NewLocation(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 120.f);
		Slot3->SetWorldLocation(NewLocation);
	}
}

void APResourceSpawner::ShowUnpickedOptions()
{
	BeginSpawn();
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

void APResourceSpawner::SetResourceForRandomizedSlot(FString ResourceName, int32 Slot) const
{
	if (ResourceName == "Copper")
	{
		SpawnForSlot(CopperClass, Slot);
	}
	else if (ResourceName == "Silver")
	{
		SpawnForSlot(SilverClass, Slot);
	}
	else if (ResourceName == "Bronze")
	{
		SpawnForSlot(BronzeClass, Slot);
	}
	else if (ResourceName == "Iron")
	{
		SpawnForSlot(IronClass, Slot);
	}
	else
	{
		SpawnForSlot(BronzeClass, Slot);
	}
}

void APResourceSpawner::SpawnForSlot(TSubclassOf<APResourceSpawnable> SpawnableClass, int32 Slot) const
{
	if (Slot == 1)
	{
		GetWorld()->SpawnActor<APResourceSpawnable>(SpawnableClass, Slot1Spawn->GetComponentLocation(),
		                                            Slot1Spawn->GetComponentRotation());
	}

	if (Slot == 2)
	{
		GetWorld()->SpawnActor<APResourceSpawnable>(SpawnableClass, Slot2Spawn->GetComponentLocation(),
		                                            Slot2Spawn->GetComponentRotation());
	}

	if (Slot == 3)
	{
		GetWorld()->SpawnActor<APResourceSpawnable>(SpawnableClass, Slot3Spawn->GetComponentLocation(),
		                                            Slot3Spawn->GetComponentRotation());
	}
}

void APResourceSpawner::ToggleBackSlots()
{
	if (PickedOption != 1)
	{
		Slot1->ToggleVisibility();
	}
	if (PickedOption != 2)
	{
		Slot2->ToggleVisibility();
	}
	if (PickedOption != 3)
	{
		Slot3->ToggleVisibility();
	}
}
