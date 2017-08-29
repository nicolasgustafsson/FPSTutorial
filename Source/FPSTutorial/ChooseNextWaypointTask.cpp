// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingComponent.h"


EBTNodeResult::Type UChooseNextWaypointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent * Blackboard = OwnerComp.GetBlackboardComponent();
	int IndexValue = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	UPatrollingComponent* PatrollingComponent = (OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrollingComponent>());
	if (PatrollingComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No patrolling component in pawn!"));
		return EBTNodeResult::Failed;
	}

	IndexValue++;
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, IndexValue);

	AActor* WaypointObject = PatrollingComponent->GetWaypointAtIndex(IndexValue);

	if (WaypointObject == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Blackboard->SetValueAsObject(TEXT("Waypoint"), WaypointObject);
	UE_LOG(LogTemp, Warning, TEXT("AI chose new waypoint!"));
	return EBTNodeResult::Succeeded;
}