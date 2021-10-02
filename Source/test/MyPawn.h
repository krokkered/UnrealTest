// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Math/Vector.h"







#include "MyPawn.generated.h"





UCLASS()
class TEST_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    //Input functions
    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void PitchCamera(float AxisValue);
    void YawCamera(float AxisValue);
    void ZoomIn(float ZoomAmount);
    void ZoomOut();
    // Called to bind functionality to input

protected:
    UPROPERTY(EditAnywhere)
        class USpringArmComponent* SpringArmComp;

    UPROPERTY(EditAnywhere)
        class UCameraComponent* CameraComp;


    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* StaticMeshComp;

    //Input variables
    FVector2D MovementInput;
    FVector2D CameraInput;
    float ZoomFactor;
    bool bZoomingIn;


};