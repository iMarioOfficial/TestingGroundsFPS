// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;
	
	//Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);  //setting the waypoint key at the [index] of patrolpoints
		//TODO protect against empty patrolroutes

	//Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num(); //index + 1 increases it to next waypoint, % arraylength makes it go in a circle for the amt of patrolpoints. if confused on 'circle', watch lecture 237
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);  

	return EBTNodeResult::Succeeded;
}

