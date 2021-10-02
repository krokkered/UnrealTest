// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController(){
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	//SpawnLocation = FVector(600.0f, 600.0f,600.0f);

	//FVector inutile = FVector(20.0f, 50.0f, 30.0f);

	//UE_LOG(LogTemp, Warning, TEXT("vec  %f"), SpawnLocation.x);
	//UE_LOG(LogTemp, Warning, TEXT("vec inutile  %s"), *SpawnLocation.ToString());






}

void AMyPlayerController::BeginPlay()
{
	 Super::BeginPlay();

	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorCube::StaticClass(), FoundActorCubes);
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorSphere::StaticClass(), FoundActorSpheres);

	 //ActorCubeRef = Cast<AActorCube>(FoundActorCubes[0]);

	 //ActorSphereRef = Cast<AActorCube>(FoundActorSpheres[0]);

}




void AMyPlayerController::SetupInputComponent()
{
	// Always call this.
	Super::SetupInputComponent();

	// This is initialized on startup, you can go straight to binding
	InputComponent->BindAction("RightMouse", IE_Pressed, this, &AMyPlayerController::RightClick);
	InputComponent->BindAction("RightMouse", IE_Released, this, &AMyPlayerController::RightClickReleased);


}


void AMyPlayerController::RightClick() {
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("right click player contron pressed"));
	
	
	AActorCube* ActorCubeRef = Cast<AActorCube>(FoundActorCubes[0]);
	ActorCubeRef->RightClick();

	AActorSphere* ActorSphereRef = Cast<AActorSphere>(FoundActorSpheres[0]);
	ActorSphereRef->RightClick();

	//Cast<AActorCube>(ActorCubeRef)->RightClick();


}


void AMyPlayerController::RightClickReleased() {
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("player control released right"));

	//AActorCube* ActorCubeRef = Cast<AActorCube>(FoundActorCubes[0]);
	//Cast<AActorCube>(ActorCubeRef)->RightClickReleased();
	//if (ActorSphereRef != nullptr)


	AActorCube* ActorCubeRef = Cast<AActorCube>(FoundActorCubes[0]);
	ActorCubeRef->RightClickReleased();
	AActorSphere* ActorSphereRef = Cast<AActorSphere>(FoundActorSpheres[0]);
	ActorSphereRef->RightClickReleased();

}

