// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShowAndIcreaseCautionBar.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "TimerManager.h"

UBTTask_ShowAndIcreaseCautionBar::UBTTask_ShowAndIcreaseCautionBar()
{
	NodeName = "Increase Caution Bar";
}

EBTNodeResult::Type UBTTask_ShowAndIcreaseCautionBar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ShowCautionBar(OwnerComp);
	IncreaseCautionBarValue(OwnerComp);
	return EBTNodeResult::Succeeded;
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
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, 0.2f, false, 0.2f);
		ControlledCharacter->CautionBarValue = ControlledCharacter->CautionBarValue++;
		UE_LOG(LogTemp, Warning, TEXT("Caution Bar Value: %f"), ControlledCharacter->CautionBarValue);
		//Needs to increment over time //FTimerHandle
	}
	else if (CautionBarPercent >= ControlledCharacter->MaxCautionBarValue)
	{
		//Change Caution Bar to red
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	//decrease if can't see player

	//Remove caution bar from screen if AI dead
}
