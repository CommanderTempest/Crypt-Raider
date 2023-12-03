// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) return;

	if (PhysicsHanle->GetGrabbedComponent != nullptr )
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	
	
	// ...
}

void UGrabber::Release() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) return;

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Grab() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) return;
	FHitResult hitResult;
	bool hasHit = GetGrabableInReach(hitResult);
	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

	}
}

bool UGrabber::GetGrabableInReach(FHitResult& OutHitResult) const 
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	// use arrow when object returns pointer
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, 
		start, 
		end, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
		);
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() {
	 return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}
