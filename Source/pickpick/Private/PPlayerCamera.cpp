// Nathaniel Richards 2021


#include "PPlayerCamera.h"
#include "PPlayerResourceManager.h"
#include "PResourceSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

APPlayerCamera::APPlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bConstrainAspectRatio = false;

	RootComponent = CameraComp;

	ResourceManager = CreateDefaultSubobject<UPPlayerResourceManager>(TEXT("Resource Manager"));
}

void APPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = Cast<APlayerController>(GetController());

	PC->bShowMouseCursor = true;
}

void APPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("CollectResource", IE_Pressed, this, &APPlayerCamera::CollectResource);
}

void APPlayerCamera::CollectResource()
{
	FHitResult Hit;

	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor
	(
		ECC_Visibility,
		true,
		Hit
	);


	APResourceSpawner* ResourceSpawner = Cast<APResourceSpawner>(
		UGameplayStatics::GetActorOfClass(this, APResourceSpawner::StaticClass()));

	ResourceSpawner->RouteCursorHit(Hit);
}
