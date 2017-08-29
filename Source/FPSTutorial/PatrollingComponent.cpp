// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingComponent.h"

AActor* UPatrollingComponent::GetWaypointAtIndex(const int WaypointIndex)
{
	if (Waypoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No waypoints in patrolling component!"));
		return nullptr;
	}
	return Waypoints[WaypointIndex % Waypoints.Num()];

}

