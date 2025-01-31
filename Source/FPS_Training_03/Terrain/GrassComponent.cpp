// Fill out your copyright notice in the Description page of Project Settings.


#include "GrassComponent.h"

UGrassComponent::UGrassComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	for (size_t i = 0; i < SpawnCount; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(SpawningExtents);
		AddInstance(FTransform(SpawnLocation));
	}
}
