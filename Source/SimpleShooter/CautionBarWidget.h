// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CautionBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UCautionBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

public:
	//void SetCautionBarPercent();
	//class AShooterCharacter* ShooterCharacterRef;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* CautionBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CautionBarCanvas;
};
