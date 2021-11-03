// Nathaniel Richards 2021

#include "Camera/CameraComponent.h"
#include "PPlayerResourceManager.h"
#include "PCharacterCamera.h"

APCharacterCamera::APCharacterCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bConstrainAspectRatio = false;

	RootComponent = CameraComp;

	ResourceManagerComp = CreateDefaultSubobject<UPPlayerResourceManager>(TEXT("ResourceManagerComp"));
}

void APCharacterCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APCharacterCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
