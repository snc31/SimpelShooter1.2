// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindNextTarget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_FindNextTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindNextTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	TArray<AActor*> GetTargetPoints(UBehaviorTreeComponent& OwnerComp);
	void SetBlackboardnKeys(UBehaviorTreeComponent& OwnerComp);
	int32 Index;

	UPROPERTY(VisibleAnywhere)
	FBlackboardKeySelector IndexKey;
};
