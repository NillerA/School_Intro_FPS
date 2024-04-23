// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	RootComponent = CollisionComponent;
	doorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (openingDoor)
	{
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / openTime * 100, 0, 100.0f);

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));

		float newZRotation;

		if (doorOpen)
		{
			newZRotation = FMath::Lerp(0.0f, 90.0f, percentage / 100);
		}
		else
		{
			newZRotation = FMath::Lerp(90.0f, 0.0f, percentage / 100);
		}

		FRotator newRotation = doorMesh->GetRelativeRotation();

		newRotation.Yaw = newZRotation;

		doorMesh->SetRelativeRotation(newRotation);

		if (percentage == 100.0f)
		{
			openingDoor = false;
			timeSinceTick = 0;
		}
	}
}

void ADoor::Use_Implementation() {
	if (!openingDoor)
	{
		doorOpen = !doorOpen;
		openingDoor = true;
	}
}