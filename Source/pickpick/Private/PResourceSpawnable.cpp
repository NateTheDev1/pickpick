// Nathaniel Richards 2021


#include "PResourceSpawnable.h"

#include "Particles/ParticleSystemComponent.h"

APResourceSpawnable::APResourceSpawnable()
{
	PrimaryActorTick.bCanEverTick = true;

	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceMesh"));
	RootComponent = ResourceMesh;

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));
}

void APResourceSpawnable::BeginPlay()
{
	Super::BeginPlay();
}

void APResourceSpawnable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APResourceSpawnable::HandleDestructionParticles() const
{
	if (UseParticles)
	{
		ParticleSystemComp->Activate(true);
	}
}
