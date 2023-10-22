// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ArrivedAtTargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

UBTTask_FindNextTarget::UBTTask_FindNextTarget()
{
	NodeName = TEXT("Find Next Target");
}

EBTNodeResult::Type UBTTask_FindNextTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	SetBlackboardnKeys(OwnerComp); //Fucntion that sets blackboard keys NextTargetPointLocation and NextTargetPointRotation
	return EBTNodeResult::Succeeded;
}

TArray<AActor*> UBTTask_FindNextTarget::GetTargetPoints(UBehaviorTreeComponent& OwnerComp)//Function gets the array of target points from an enemy ai character
{
	AAIController* OwnerController = OwnerComp.GetAIOwner(); //get the AI controller thats connected to the behaviour tree
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(OwnerController->GetPawn()); //Cast to the shooter character type and get the pawn enemy.
	TArray<AActor*> EnemyTargetPoints = ControlledCharacter->TargetPoints; //get the target points that are connected to the pawn enemy that was received
	return EnemyTargetPoints;
}

void UBTTask_FindNextTarget::SetBlackboardnKeys(UBehaviorTreeComponent& OwnerComp) //Fucntion that sets blackboard keys NextTargetPointLocation and NextTargetPointRotation
{
	Index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("Index")); //Set Index variable to Index blackboard key value
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), GetTargetPoints(OwnerComp)[Index]->GetActorLocation()); //Set the NextTargetPointLocation to the target point of position Index from the target point array
	OwnerComp.GetBlackboardComponent()->SetValueAsRotator(TEXT("NextTargetPointRotation"), GetTargetPoints(OwnerComp)[Index]->GetActorRotation()); //Set the NextTargetPointRotation to the target point of position Index from the target point array
}
