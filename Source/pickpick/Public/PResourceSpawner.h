// Nathaniel Richards 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PResourceSpawner.generated.h"

UCLASS()
class PICKPICK_API APResourceSpawner : public AActor
{
	GENERATED_BODY()

public:
	APResourceSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float SpawnDelay = 1.f;

public:
	virtual void Tick(float DeltaTime) override;
private:
	void Spawn();

	// Values 0, 1, 2
	void ShowOption(int32 Index);

	void ShowUnpickedOptions();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Slot1;

	UPROPERTY(EditAnywhere)
	USceneComponent* Slot1Spawn;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Slot2;

	UPROPERTY(EditAnywhere)
	USceneComponent* Slot2Spawn;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Slot3;

	UPROPERTY(EditAnywhere)
	USceneComponent* Slot3Spawn;

	static FString GetResourceType(int32 Index);
};
