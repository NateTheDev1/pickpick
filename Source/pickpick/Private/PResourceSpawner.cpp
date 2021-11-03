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

	if (!Spawning)
	{
		FHitResult Hit;

		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor
		(
			ECC_Visibility,
			true,
			Hit
		);

		if (Hit.GetComponent() && !HasRevealed)
		{
			if (Hit.Component->GetName().Contains("Slot"))
			{
				FString NewName = Hit.Component->GetName();

				NewName.RemoveFromStart("Slot");

				ShowOption(FCString::Atoi(*NewName));
			}
		}
		if (HasRevealed && Hit.GetComponent() && Hit.GetActor())
		{
			if (Hit.GetActor()->GetClass()->IsChildOf(APResourceSpawnable::StaticClass()))
			{
				const APResourceSpawnable* Spawnable = Cast<APResourceSpawnable>(Hit.GetActor());

				UE_LOG(LogTemp, Warning, TEXT("%s"), *Spawnable->Name);
			}
		}
	}
}

void APResourceSpawner::BeginSpawn()
{
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


	UE_LOG(LogTemp, Warning, TEXT("%s"), *Slot1Randomized);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Slot2Randomized);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Slot3Randomized);

	Spawning = false;
}

void APResourceSpawner::ShowOption(int32 Index)
{
	HasRevealed = true;

	UE_LOG(LogTemp, Warning, TEXT("%i"), Index);


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
