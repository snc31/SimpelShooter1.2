// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShowAndIcreaseCautionBar.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Blueprint/UserWidget.h"
#include "CautionBarWidget.h"
#include "Components/ProgressBar.h"
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
	CautionBarWidgetComponentRef = ControlledCharacter->CautionBarWidget;
	//CautionBarWidgetRef = Cast<UCautionBarWidget>(CautionBarWidgetComponentRef->GetWidget());

	if (CautionBarWidgetComponentRef != nullptr)
	{
		CautionBarWidgetComponentRef->SetHiddenInGame(false);
	}
}

void UBTTask_ShowAndIcreaseCautionBar::IncreaseCautionBarValue(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner(); //get the AI controller thats connected to the behaviour tree
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(OwnerController->GetPawn()); //Cast to the shooter character type and get the pawn enemy.
	float CautionBarPercent = ControlledCharacter->GetCautionBarPercent(); //Store the float percent that is returned from shootercharacter.cpp
	CautionBarWidgetComponentRef = ControlledCharacter->CautionBarWidget; //Get a reference to the widget component
	CautionBarWidgetRef = Cast<UCautionBarWidget>(CautionBarWidgetComponentRef->GetWidget()); //Get a reference tot he widget on the widget component

	if (ControlledCharacter->CautionBarValue < ControlledCharacter->MaxCautionBarValue)
	{
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle, 0.2f, false, 0.2f); //Timer between every percent increase
		ControlledCharacter->IncreaseCautionBarValue(); //Increase the float value CautionBarValue which in ShooterCharacter
		CautionBarWidgetRef->CautionBar->SetPercent(CautionBarPercent); //Set the progressbar value to the percent value
	}
	else if (ControlledCharacter->CautionBarValue >= ControlledCharacter->MaxCautionBarValue)
	{
		CautionBarWidgetRef->CautionBar->SetFillColorAndOpacity(FColor::Red); //Set Caution bar progress bar to red
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle, 20.f, false, 20.f); //wait time before removing caution bar from screen
		CautionBarWidgetComponentRef->SetHiddenInGame(true); //Hide caution bar from view
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true); //set balckboard key IsCautionBarFull? to true
	}
}
	//Decrease if can't see player and under max cuation bar value

	//Hide if bar reaches 0

	//Remove caution bar from screen if AI dead
