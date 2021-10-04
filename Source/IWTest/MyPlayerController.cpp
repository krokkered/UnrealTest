// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController(){
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;


}

void AMyPlayerController::BeginPlay()
{
	 Super::BeginPlay();

	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorCube::StaticClass(), FoundActorCubes);
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorSphere::StaticClass(), FoundActorSpheres);


}




void AMyPlayerController::SetupInputComponent()
{
	// Always call this.
	Super::SetupInputComponent();

	InputComponent->BindAction("RightMouse", IE_Pressed, this, &AMyPlayerController::RightClick);
	InputComponent->BindAction("RightMouse", IE_Released, this, &AMyPlayerController::RightClickReleased);


}


void AMyPlayerController::RightClick() {
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("right click player contron pressed"));
	
	
	AActorCube* ActorCubeRef = Cast<AActorCube>(FoundActorCubes[0]);
	ActorCubeRef->RightClick();

	AActorSphere* ActorSphereRef = Cast<AActorSphere>(FoundActorSpheres[0]);
	ActorSphereRef->RightClick();



}


void AMyPlayerController::RightClickReleased() {
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("player control released right"));

	AActorCube* ActorCubeRef = Cast<AActorCube>(FoundActorCubes[0]);
	ActorCubeRef->RightClickReleased();
	AActorSphere* ActorSphereRef = Cast<AActorSphere>(FoundActorSpheres[0]);
	ActorSphereRef->RightClickReleased();

}

