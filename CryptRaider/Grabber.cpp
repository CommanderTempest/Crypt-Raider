// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Display, TEXT("Released"));
}

void UGrabber::Grab() {
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	// use arrow when object returns pointer
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		start, 
		end, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
		);
}
