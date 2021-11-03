// Nathaniel Richards 2021

#pragma once

#include "CoreMinimal.h"
#include "PResourceSpawnable.h"
#include "Components/ActorComponent.h"
#include "PPlayerResourceManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PICKPICK_API UPPlayerResourceManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPPlayerResourceManager();

	int32 GatherToolType = 0;

	int32 Level = 1;
	float CurrentXP = 0.f;
	float Money = 0.0f;

	void AddMoney(float Amount);
	void RemoveMoney(float Amount);

	void AddResource(float Amount, int32 ResourceType);

	float BronzeCount = 0.0f;
	float CopperCount = 0.0f;
	float IronCount = 0.0f;
	float GoldCount = 0.0f;
	float PlatinumCount = 0.0f;
	float DiamondCount = 0.0f;
	float SilverCount = 0.0f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	float LevelXPModifier = 1.3f;

	int32 GetXPToNextLevel() const;

	void LevelIncrease();
};
