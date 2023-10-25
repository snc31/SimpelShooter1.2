// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShowAndIcreaseCautionBar.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_ShowAndIcreaseCautionBar : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ShowAndIcreaseCautionBar();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	void ShowCautionBar(UBehaviorTreeComponent& OwnerComp);
	class UWidgetComponent* CautionBarWidgetRef;
	TArray<USceneComponent>* AIComponents;
};
