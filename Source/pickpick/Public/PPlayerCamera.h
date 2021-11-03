// Nathaniel Richards 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPlayerCamera.generated.h"

class UCameraComponent;
class UPPlayerResourceManager;

UCLASS()
class PICKPICK_API APPlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	APPlayerCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	UPPlayerResourceManager* ResourceManager;
};
