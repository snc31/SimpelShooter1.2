// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ArrivedAtTargetPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

UBTTask_ArrivedAtTargetPoint::UBTTask_ArrivedAtTargetPoint()
{
	NodeName = TEXT("Arrived At Target Point");
}

EBTNodeResult::Type UBTTask_ArrivedAtTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//set the blackboard key for the target point array by calling function
	SetBlackboardIndexKey(OwnerComp);
	return EBTNodeResult::Type();
}

TArray<AActor*> UBTTask_ArrivedAtTargetPoint::GetTargetPoints(UBehaviorTreeComponent& OwnerComp) //Function gets the array of target points from an enemy ai character
{
	AAIController* OwnerController = OwnerComp.GetAIOwner(); //get the AI controller thats connected to the behaviour tree
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(OwnerController->GetPawn()); //Cast to the shooter character type and get the pawn enemy.
	TArray<AActor*> EnemyTargetPoints = ControlledCharacter->TargetPoints; //get the target points that are connected to the pawn enemy that was received
	return EnemyTargetPoints;
}

void UBTTask_ArrivedAtTargetPoint::SetBlackboardIndexKey(UBehaviorTreeComponent& OwnerComp) //This funtion needs to be called and executed
{
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), TargetPointIndex(OwnerComp)); //Set the blackboard key Index for the next patrol point to be found from the FindNextTarget class.
}

int32  UBTTask_ArrivedAtTargetPoint::TargetPointIndex(UBehaviorTreeComponent& OwnerComp) //The Index increment logic
{
	NumberOfTargetPoints = GetTargetPoints(OwnerComp).Num(); //Length of the array of target points
	MaxIndex = NumberOfTargetPoints - 1; //Array size -1 for index
	Index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey()); //Set Index variable value to the Index blackboard key. 
	if (Index >= MaxIndex)
	{
		Index = MinIndex;
	}
	else
	{
		Index++;
	}
	return Index;
}

bool UBTTask_ArrivedAtTargetPoint::bIsLooping(UBehaviorTreeComponent& OwnerComp) //for future implementation of patrol points tool
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(OwnerController->GetPawn());
	if (ControlledCharacter->bLooping)
	{
		return true;
	}
	else
	{
		return false;
	}
}
