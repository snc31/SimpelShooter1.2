// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShowAndIcreaseCautionBar.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

UBTTask_ShowAndIcreaseCautionBar::UBTTask_ShowAndIcreaseCautionBar()
{
	NodeName = "Increase Caution Bar";
}

EBTNodeResult::Type UBTTask_ShowAndIcreaseCautionBar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ShowCautionBar(OwnerComp);
	IncreaseCautionBarValue(OwnerComp);
	return EBTNodeResult::InProgress;
}

void UBTTask_ShowAndIcreaseCautionBar::ShowCautionBar(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner(); //get the AI controller thats connected to the behaviour tree
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(OwnerController->GetPawn()); //Cast to the shooter character type and get the pawn enemy.
	CautionBarWidgetRef = ControlledCharacter->CautionBarWidget;

	if (CautionBarWidgetRef != nullptr)
	{
		CautionBarWidgetRef->SetHiddenInGame(false);
	}
}

void UBTTask_ShowAndIcreaseCautionBar::IncreaseCautionBarValue(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner(); //get the AI controller thats connected to the behaviour tree
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(OwnerController->GetPawn()); //Cast to the shooter character type and get the pawn enemy.
	float CautionBarPercent = ControlledCharacter->CautionBarValue;
	if (CautionBarPercent < ControlledCharacter->MaxCautionBarValue)
	{
		CautionBarPercent++;
		//Needs to increment over time //FTimerHandle
	}
	//else if (CautionBarPercent >= ControlledCharacter->MaxCautionBarValue)
	//{
	//	//Change Caution Bar to red
	//}
	//decrease if can't see player
}
