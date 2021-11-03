// Nathaniel Richards 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PResourceSpawnable.generated.h"


UCLASS()
class PICKPICK_API APResourceSpawnable : public AActor
{
	GENERATED_BODY()

public:
	APResourceSpawnable();
	
	UPROPERTY(EditAnywhere)
	FString Name = TEXT("ResourceDefaultName");

	UPROPERTY(EditAnywhere)
	float ResourceValueInMoney = 10.f;

	UPROPERTY(EditAnywhere)
	float ResourceValueInResources = 1.0f;

	UPROPERTY(EditAnywhere)
	float XPGain = 5.f;

	UPROPERTY(EditAnywhere)
	int32 ResourceType = 0;

	UPROPERTY(EditAnywhere)
	TArray<int32> BreakableBy = {0};
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ResourceMesh;

	// Optional Usage For Particles On break
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComp;

	UPROPERTY(EditAnywhere)
	bool UseParticles = false;

	void HandleDestructionParticles() const;

	// Amount of times the user needs to click to collect the resource
	UPROPERTY(EditAnywhere)
	float ResourceHealth = 1.f;
};
