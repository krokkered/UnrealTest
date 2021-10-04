// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSphere.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h" 
//#include "MyPawn.h"


// Sets default values
AActorSphere::AActorSphere()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
    //Mesh->SetupAttachment(RootComponent);

    SetRootComponent(Mesh);
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

    SphereMesh = SphereAsset.Object;

    if (SphereMesh != nullptr)
    {
        Mesh->SetStaticMesh(SphereMesh);


    }

    OnBeginCursorOver.AddDynamic(this, &AActorSphere::CustomOnBeginMouseOver);
    OnEndCursorOver.AddDynamic(this, &AActorSphere::CustomOnEndMouseOver);

    }

// Called when the game starts or when spawned
void AActorSphere::BeginPlay()
{
    Super::BeginPlay();
    BindToInput();



}



// Called every frame
void AActorSphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    AMyPawn* pawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (CanRotate) {

        float dx, dy;
        GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(dx, dy);





        pawn->YawCamera(dx);
        pawn->PitchCamera(dy);


    }
    
    else { 

        //avoids camera to spin around 

        pawn->YawCamera(0);
        pawn->PitchCamera(0);
    }


}

void AActorSphere::CustomOnBeginMouseOver(AActor* Actor)
{
    if (GEngine)
    {
        this->IsHovered = true;

    }


    AMyPlayerController* MyPc = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (MyPc)
    {
        MyPc->CurrentMouseCursor = EMouseCursor::GrabHand;

    }
}


void AActorSphere::CustomOnEndMouseOver(AActor* Actor)
{



    AMyPlayerController* MyPc = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (MyPc)
    {


        MyPc->CurrentMouseCursor = EMouseCursor::Default;
        IsHovered = false;

    }
}



void AActorSphere::RightClick() {


    if (IsHovered) {


        CanRotate = true;
    }



}

void AActorSphere::RightClickReleased() {

    CanRotate = false;
}


void AActorSphere::Zoom(float amount) {

    if (IsHovered) {

        AMyPawn* pawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


        pawn->ZoomIn(amount);
    }

}





void AActorSphere::BindToInput()
{
    // Initialize our component
    InputComponent = NewObject<UInputComponent>(this);
    InputComponent->RegisterComponent();

    if (InputComponent)
    {


        InputComponent->BindAxis("MouseWheel", this, &AActorSphere::Zoom);

        EnableInput(GetWorld()->GetFirstPlayerController());
    }
}


