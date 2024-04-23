// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureZone.h"

// Sets default values
ACaptureZone::ACaptureZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	flagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
	poleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole"));

	RootComponent = CollisionComponent;
	poleMesh->SetupAttachment(RootComponent);
	flagMesh->SetupAttachment(RootComponent);
	flagState = EFlagState::DOWN;
}

// Called when the game starts or when spawned
void ACaptureZone::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACaptureZone::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACaptureZone::OnOverlapEnd);
}

void ACaptureZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*capturing = true;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Yellow, TEXT("Colliding"));
	}*/
}

void ACaptureZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*capturing = false;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Yellow, TEXT("Not Colliding"));
	}*/
}

// Called every frame
void ACaptureZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (capturing)
	{
		timeSinceTick += DeltaTime;
		
		percentage = FMath::Clamp(timeSinceTick / captureTime * 100, 0, 100.0f);

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));

		float newZPosition;

		if (flagState == EFlagState::DOWN)
		{
			newZPosition = FMath::Lerp(-17.0f, 29.0f, percentage / 100);
		}
		else if(flagState == EFlagState::UP)
		{
			newZPosition = FMath::Lerp(29.0f, -17.0f, percentage / 100);
		}

		FVector newLocation = flagMesh->GetRelativeLocation();

		newLocation.Z = newZPosition;

		flagMesh->SetRelativeLocation(newLocation);

		if (percentage == 100.0f)
		{
			capturing = false;
			timeSinceTick = 0;

			flagState = (flagState == EFlagState::DOWN) ? EFlagState::UP : EFlagState::DOWN;
		}
	}

}

void ACaptureZone::Use_Implementation() {
	capturing = true;
}