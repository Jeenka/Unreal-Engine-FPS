// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout()
{
	if (Pool.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actors in pool"));
		return nullptr;
	}
	return Pool.Pop();
}

void UActorPool::ReturnActor(AActor* ActorToReturn)
{
	UE_LOG(LogTemp, Warning, TEXT("Return call"));
	AddActor(ActorToReturn);
}

void UActorPool::AddActor(AActor* ActorToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Add call"));
	Pool.Push(ActorToAdd);
}
