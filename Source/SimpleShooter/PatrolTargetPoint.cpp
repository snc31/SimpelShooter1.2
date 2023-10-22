// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolTargetPoint.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
APatrolTargetPoint::APatrolTargetPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//set up static mesh and attach to root component
	TargetPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Point Mesh"));
	TargetPointMesh->SetupAttachment(Root);

	//set up an arrow and attach to root component
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APatrolTargetPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolTargetPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

