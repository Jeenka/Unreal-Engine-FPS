// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointCyclingBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"

EBTNodeResult::Type UWaypointCyclingBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 CurrentWaypointIndex = BlackboardComp->GetValueAsInt(WaypointIndex.SelectedKeyName);
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute))
	{
		UE_LOG(LogTemp, Warning, TEXT("No route component"));
		return EBTNodeResult::Failed;
	}
	else if (!ensure(PatrolRoute->GetWaypointsCount() > 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Waypoints count is [ %i ]"), PatrolRoute->GetWaypointsCount());
		return EBTNodeResult::Failed;
	}
	else if (!ensure(PatrolRoute->GetWaypointByIndex(CurrentWaypointIndex)))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ %i ] waypoint is empty"), CurrentWaypointIndex);
		return EBTNodeResult::Failed;
	}
	BlackboardComp->SetValueAsObject(WaypointObject.SelectedKeyName, PatrolRoute->GetWaypointByIndex(CurrentWaypointIndex));
	CurrentWaypointIndex = (CurrentWaypointIndex + 1) % PatrolRoute->GetWaypointsCount();
	BlackboardComp->SetValueAsInt(WaypointIndex.SelectedKeyName, CurrentWaypointIndex);

	return EBTNodeResult::Succeeded;
}
