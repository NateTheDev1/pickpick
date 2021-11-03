// Nathaniel Richards 2021


#include "PPlayerResourceManager.h"

UPPlayerResourceManager::UPPlayerResourceManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPPlayerResourceManager::BeginPlay()
{
	Super::BeginPlay();
}


void UPPlayerResourceManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
