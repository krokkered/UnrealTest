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


    //UE_LOG(LogTemp, Warning, TEXT("loc  %d"), IsHovered);

}



// Called every frame
void AActorSphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (CanRotate) {

        float dx, dy;
        GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(dx, dy);

        //FRotator NewRotation = FRotator(dy * -10, dx * -10, 0.f);


        AMyPawn* pawn = Cast<AMyPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


        pawn->YawCamera(dx);
        pawn->PitchCamera(dy);


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
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Mouse Over"));

    }


    AMyPlayerController* MyPc = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (MyPc)
    {


        MyPc->CurrentMouseCursor = EMouseCursor::Default;
        IsHovered = false;

    }
}



void AActorSphere::RightClick() {


    if (IsHovered) {

        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("onSphere to change r"));

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

        //InputComponent->BindAction("RightMouse", IE_Pressed, this, &AActorSphere::RightClick);
       // InputComponent->BindAction("RightMouse", IE_Released, this, &AActorSphere::RightClickReleased);

        InputComponent->BindAxis("MouseWheel", this, &AActorSphere::Zoom);

        EnableInput(GetWorld()->GetFirstPlayerController());
    }
}


