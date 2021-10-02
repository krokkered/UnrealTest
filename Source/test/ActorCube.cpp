// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorCube.h"


// Sets default values
AActorCube::AActorCube()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
    Mesh->SetupAttachment(RootComponent);

    
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> ConeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

    CylinderMesh = CylinderAsset.Object;
    CubeMesh =CubeAsset.Object;
    ConeMesh = ConeAsset.Object;

    if (CubeMesh != nullptr)
    {
        Mesh->SetStaticMesh(CubeMesh);


    }

    OnBeginCursorOver.AddDynamic(this, &AActorCube::CustomOnBeginMouseOver);
    OnEndCursorOver.AddDynamic(this, &AActorCube::CustomOnEndMouseOver);



    //OnBeginCursorOver.AddDynamic(this, &AActorCube::CustomOnBeginMouseOver);
}

// Called when the game starts or when spawned
void AActorCube::BeginPlay()
{
	Super::BeginPlay();
    BindToInput();

    CentralClickCount = 0;



    auto Material = Mesh->GetMaterial(0);


    DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);

    Mesh->SetMaterial(0, DynamicMaterial);

}



// Called every frame
void AActorCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (CanRotate) {

        float dx, dy;
        GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(dx, dy);

        FRotator NewRotation = FRotator(dy*-10,  dx * -10 , 0.f);

        //AddActorLocalRotation(NewRotation, false, 0, ETeleportType::None);
        AddActorWorldRotation(NewRotation, false, 0, ETeleportType::None);


    }

    if (ToggleSelfRotation) {

        AddActorLocalRotation(FRotator(3.f, 0.f, 0.f));

    }

    FVector CurrentLoc = GetActorLocation();
   // IncreasingAngle = FMath::Fmod(IncreasingAngle + (40 * DeltaTime), 360);
    //if (IncreasingAngle > 360) IncreasingAngle = 1;


   // int rx, ry;

        /* IncreasingAngle += DeltaTime * 50;

        if (IncreasingAngle > 360) IncreasingAngle = 1;

        FVector CurrentLoc = GetActorLocation();


        FVector SphereLoc = FVector(0, 200, 0); //where the sphere is, 

        FVector NewLoc = FVector(0, 200, 0); //center of rotation
        
        float radius = FMath::Sqrt(FMath::Square(NewLoc.X -CurrentLoc.X     ) + FMath::Square(NewLoc.Y - CurrentLoc.Y) );



        GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("radius %f"), radius));


        FVector RotateValue = FVector(radius, 0, 0).RotateAngleAxis(IncreasingAngle, FVector(0, 0, 1));

        NewLoc.X += RotateValue.X;
        NewLoc.Y += RotateValue.Y;
        NewLoc.Z += RotateValue.Z+ CurrentLoc.Z;



    //    ry = FMath::Sin(IncreasingAngle*50) * r;
      //  rx = FMath::Cos(IncreasingAngle*50) * r;

        

        SetActorLocation(NewLoc);
        */
 
    //GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("Location %s"), *GetActorLocation().ToString()));
    //UE_LOG(LogTemp, Warning, TEXT("loc  %f %f %f"), CurrentLoc.X, CurrentLoc.Y);

        FVector NewLoc = FVector(0, 200, 0); //center of rotation

        //if (radius < 50) radius = 60;
        //radius = 200;
      //  GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("radius %f"), radius));





     /* if (!(ToggleRevolution)) {

            float angolo2 =FGenericPlatformMath::Atan2(CurrentLoc.X , CurrentLoc.Y);
            float angolo = FGenericPlatformMath::Atan(CurrentLoc.X/ CurrentLoc.Y);

                GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT("arctan %f"), FMath::RadiansToDegrees<float>(angolo)));

            GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT("arcta2n %f"), angolo2));

            IncreasingAngle = FMath::RadiansToDegrees<float>(angolo2);
            //IncreasingAngle = FMath::Fmod(IncreasingAngle + (40 * DeltaTime), 360);


            SetActorLocation
        }
        */

       //  GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("angolorot %f"), IncreasingAngle));


    if (ToggleRevolution ) {

        float radius = FMath::Sqrt(FMath::Square(CurrentLoc.X - NewLoc.X) + FMath::Square(CurrentLoc.Y - NewLoc.Y));

        float CurrentValueInRadians = FMath::DegreesToRadians<float>(IncreasingAngle);

        IncreasingAngle = FMath::Fmod(IncreasingAngle + (40 * DeltaTime), 360);
        if (IncreasingAngle > 360) IncreasingAngle = 1;
        float angolo2 = FGenericPlatformMath::Atan2(CurrentLoc.X, CurrentLoc.Y);
        float angolo = FGenericPlatformMath::Atan(CurrentLoc.X / CurrentLoc.Y);


        SetActorLocation(FVector(radius * FMath::Cos(CurrentValueInRadians) + NewLoc.X, radius * FMath::Sin(CurrentValueInRadians) + NewLoc.Y, CurrentLoc.Z + NewLoc.Z));

       // GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("angolorot %f"), IncreasingAngle));
    }
        

    


}

void AActorCube::CustomOnBeginMouseOver(AActor* Actor)
{
    if (GEngine)
    {
        this->IsHovered = true;

    }



    AMyPlayerController* MyPc = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (MyPc)
    {
        MyPc->CurrentMouseCursor = EMouseCursor::Crosshairs;

    }
}


void AActorCube::CustomOnEndMouseOver(AActor* Actor)
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


void AActorCube::LeftClick() {
    if (this->IsHovered) {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("oncube to change"));

        int32 seed = (int32)(FDateTime::Now().GetTicks() % INT_MAX);
        FMath::RandInit(seed);
        FLinearColor newColour = FLinearColor(FMath::FRandRange(0.000f, 1.000f), FMath::FRandRange(0.000f, 1.000f), FMath::FRandRange(0.000f, 1.000f), 1);

        DynamicMaterial->SetVectorParameterValue(TEXT("Colour1"), newColour);
    }

}

void AActorCube::RightClick() {

    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("oncube to change r"));

    if (IsHovered)
    CanRotate = true;
    //float dx, dy;
   /* GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(dx, dy);
    UE_LOG(LogTemp, Warning, TEXT("dx dy %f %f"), dx, dy);
    FRotator NewRotation = FRotator(dx*100, dy*100, 0.f);
    FQuat QuatRotation = FQuat(NewRotation);
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);*/


}

void AActorCube::RightClickReleased() {

        CanRotate = false;
}



void AActorCube::ResetRotation() {


    SetActorRotation(FRotator(0.f,0.f,0.f), ETeleportType::None);


}




void AActorCube::CentralClick() {
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("oncube to change c"));

    if (IsHovered) {

        CentralClickCount++;

        switch (CentralClickCount % 3) {
        case 0:
            if (CubeMesh != nullptr)
            {
                Mesh->SetStaticMesh(CubeMesh);
            }
            break;

        case 1:
            if (CylinderMesh != nullptr)
            {
                Mesh->SetStaticMesh(CylinderMesh);
            }
            break;

        default:

            if (ConeMesh != nullptr)
            {
                Mesh->SetStaticMesh(ConeMesh);
            }
            break;

        }
    }
}

void AActorCube::MoveForward(float amount) {




    AddActorWorldOffset(FVector(0.f, 0.f, amount));
   // AddActorLocalOffset(FVector(0.f, 0.f, amount));



}


void AActorCube::MoveRight(float amount) {


    //AddActorWorldOffset(FVector(0.f, amount, 0.f));
    //FVector CL = GetActorLocation();
    //SetActorLocation(FVector(CL.X, CL.Y+amount, CL.Z));
    AddActorLocalOffset(FVector(0.f, amount, 0.f));

}

void AActorCube::Revolution()
{
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("toggled revolution"));

    ToggleRevolution = !ToggleRevolution;



}

void AActorCube::SelfRotate()
{
    ToggleSelfRotation = !ToggleSelfRotation;
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("toggled rotation"));


}

void AActorCube::checkHorizontalMovPressed(){

    ToggleHorizontalMov = true;

}

void AActorCube::checkHorizontalMovReleased() {

    ToggleHorizontalMov = false;

}
void AActorCube::BindToInput()
{
    // Initialize our component

    InputComponent = NewObject<UInputComponent>(this);
    InputComponent->RegisterComponent();

    if (InputComponent)
    {
        // Bind inputs here
        InputComponent->BindAction("LeftMouse", IE_Released, this, &AActorCube::LeftClick);
        InputComponent->BindAction("CentralMouse", IE_Released, this, &AActorCube::CentralClick);
        // InputComponent->BindAction("RightMouse", IE_Pressed, this, &AActorCube::RightClick);
        // InputComponent->BindAction("RightMouse", IE_Released, this, &AActorCube::RightClickReleased);

       // FInputActionBinding& BindingRighPressed = InputComponent->BindAction("RightMouse", IE_Pressed, this, &AActorCube::RightClick);
        //BindingRighPressed.bConsumeInput = false;


       // FInputActionBinding& BindingRighReleased = InputComponent->BindAction("RightMouse", IE_Released, this, &AActorCube::RightClickReleased);
       // BindingRighPressed.bConsumeInput = false;


          InputComponent->BindAction("Reset", IE_Released, this, &AActorCube::ResetRotation);


          InputComponent->BindAction("RevolutionAroundSphere", IE_Released, this, &AActorCube::Revolution);
          InputComponent->BindAction("SelfRotation", IE_Released, this, &AActorCube::SelfRotate);

          InputComponent->BindAction("checkHorizontalMovement", IE_Pressed, this, &AActorCube::checkHorizontalMovPressed);
          InputComponent->BindAction("checkHorizontalMovement", IE_Released, this, &AActorCube::checkHorizontalMovReleased);



       InputComponent->BindAxis("MoveForward", this, &AActorCube::MoveForward);
          InputComponent->BindAxis("MoveRight", this, &AActorCube::MoveRight);
        // etc...

        // Now hook up our InputComponent to one in a Player
        // Controller, so that input flows down to us
        EnableInput(GetWorld()->GetFirstPlayerController());
    }    
}

