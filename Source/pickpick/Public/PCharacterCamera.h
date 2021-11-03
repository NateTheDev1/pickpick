// Nathaniel Richards 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCharacterCamera.generated.h"

class UCameraComponent;
class UPPlayerResourceManager;

UCLASS()
class PICKPICK_API APCharacterCamera : public AActor
{
	GENERATED_BODY()

public:
	APCharacterCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	UPPlayerResourceManager* ResourceManagerComp;
};
