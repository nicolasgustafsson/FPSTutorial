// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"

class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTUTORIAL_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//Will modulo index to protect out of bounds
	AActor* GetWaypointAtIndex(const int WaypointIndex);
		
private:

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<AActor*> Waypoints;
};
