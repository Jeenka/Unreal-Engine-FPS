// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/NavigationSystemBase.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtent = FVector{ 0.f, -2000.f, 0 };
	MaxnExtent = FVector{ 4000.f, 2000.f, 0 };
	NavigationVolumeOffset = FVector{ 2000.f, 0, 0 };
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (NavMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actor to return"));
		return;
	}
	NavMeshPool->ReturnActor(NavMesh);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int32 NumberToSpawn = FMath::FRandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition NewSpawnPosition;
		NewSpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);

		if (FindEmptyLocation(NewSpawnPosition.Position, Radius * NewSpawnPosition.Scale))
		{
			NewSpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, NewSpawnPosition);
		}
	}
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, 1, 1);
}

void ATile::SetPool(UActorPool* InPool)
{
	NavMeshPool = InPool;
	NavMesh = NavMeshPool->Checkout();
	if (NavMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough actors in pool"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Location set"));
	NavMesh->SetActorLocation(GetActorLocation() + NavigationVolumeOffset);
	FNavigationSystem::Build(*GetWorld());
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, FVector{ GlobalLocation.X, GlobalLocation.Y, GlobalLocation.Z + 0.1f}, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	
	return !HasHit;
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	FBox Bounds{ MinExtent, MaxnExtent };
	int32 MaxAttempts = 100;
	for (size_t i = 0; i < MaxAttempts; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Spawned->SetActorRelativeLocation(SpawnPosition.Position);
	Spawned->SetActorRotation(FRotator{0, SpawnPosition.Rotation, 0});
	Spawned->SetActorScale3D(FVector{ SpawnPosition.Scale });
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Spawned->SetActorRelativeLocation(SpawnPosition.Position);
	Spawned->SetActorRotation(FRotator{ 0, SpawnPosition.Rotation, 0 });
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));
}
