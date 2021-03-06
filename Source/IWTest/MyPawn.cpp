// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"
//#include "Camera/Component.h" //4.26?
#include "Camera/CameraComponent.h"





// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //Create our components
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

    //Attach our components
    StaticMeshComp->SetupAttachment(RootComponent);
    SpringArmComp->SetupAttachment(StaticMeshComp);
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);


    //initial camera position
    SpringArmComp->SetRelativeLocationAndRotation(FVector(-450.0f, 0.0f, 20.0f), FRotator(0.0f, 0.0f, 0.0f));

    
    SpringArmComp->TargetArmLength = 100.0f;
   // SpringArmComp->bEnableCameraLag = true;
    //SpringArmComp->CameraLagSpeed = 3.0f;

    AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    {

  
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += CameraInput.X;
        SetActorRotation(NewRotation);
        


    }

    {
        FRotator NewRotation = SpringArmComp->GetComponentRotation();
        NewRotation.Pitch += CameraInput.Y;
        SetActorRotation(NewRotation);

        
                SpringArmComp->SetWorldRotation(NewRotation);
    }

    

}

// Called to bind functionality to input


//Input functions
void AMyPawn::MoveForward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void AMyPawn::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void AMyPawn::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void AMyPawn::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

void AMyPawn::ZoomIn(float ZoomAmount)
{
    bZoomingIn = true;

    SpringArmComp->TargetArmLength +=  ZoomAmount *20;

}

void AMyPawn::ZoomOut()
{
    bZoomingIn = false;
}


