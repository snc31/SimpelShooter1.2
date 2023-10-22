// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Shoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

UBT_Shoot::UBT_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBT_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Character->Shoot();
	
	return EBTNodeResult::Succeeded;
}
