// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "UseableInterface.h"
#include "CaptureZone.generated.h"

UENUM(BlueprintType)
enum class EFlagState : uint8
{
	UP,
	DOWN
};

UCLASS()
class SCHOOL_INTRO_FPS_API ACaptureZone : public AActor, public IUseableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaptureZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* poleMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* flagMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float captureTime;

	/** called when something enters the sphere component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float timeSinceTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CaptureZone Info")
	float percentage;

	bool capturing;

	EFlagState flagState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Use_Implementation() override;

};
