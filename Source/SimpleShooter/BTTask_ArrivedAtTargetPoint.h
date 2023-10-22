// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ArrivedAtTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_ArrivedAtTargetPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ArrivedAtTargetPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	TArray<AActor*> GetTargetPoints(UBehaviorTreeComponent& OwnerComp);
	void SetBlackboardIndexKey(UBehaviorTreeComponent& OwnerComp);
	int32 TargetPointIndex(UBehaviorTreeComponent& OwnerComp);
	int32 NumberOfTargetPoints;
	int32 MinIndex = 0;
	int32 MaxIndex;
	int32 Index;
	bool bIsLooping(UBehaviorTreeComponent& OwnerComp);
};
