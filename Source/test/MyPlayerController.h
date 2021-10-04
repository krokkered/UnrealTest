// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector.h"
#include "Camera/CameraComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "GameFramework/Actor.h"

#include "ActorCube.h"
#include "ActorSphere.h"


#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class IWTEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;


	UFUNCTION()
		void RightClick();
	UFUNCTION()
		void RightClickReleased();

protected:
	TArray<AActor*> FoundActorSpheres;
	TArray<AActor*> FoundActorCubes;

};



