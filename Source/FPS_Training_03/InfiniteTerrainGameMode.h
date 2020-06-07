// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPS_Training_03GameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TRAINING_03_API AInfiniteTerrainGameMode : public AFPS_Training_03GameMode
{
	GENERATED_BODY()

public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Navmesh Bounds")
	void PopulateNavMesh();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsPool;

private:

	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
	
};
