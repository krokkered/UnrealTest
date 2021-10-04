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
        //AddActorWorldRotation(FRotator(3.f, 0.f, 0.f));
    }

    FVector CurrentLoc = GetActorLocation();

 
    //GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("Location %s"), *GetActorLocation().ToString()));
    //UE_LOG(LogTemp, Warning, TEXT("loc  %f %f %f"), CurrentLoc.X, CurrentLoc.Y);

        FVector CenterLoc = FVector(0, 200, 0); //center of rotation








        //float radius = FMath::Sqrt(FMath::Square(CurrentLoc.X - NewLoc.X) + FMath::Square(CurrentLoc.Y - NewLoc.Y));

     //  GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("pv %f %f"), previousPos.X, previousPos.Y));


        //float CurrentValueInRadians = FMath::DegreesToRadians<float>(IncreasingAngle);

        //IncreasingAngle = FMath::Fmod(IncreasingAngle + (40 * DeltaTime), 360);
        //if (IncreasingAngle > 360) IncreasingAngle = 1;

        //FVector newPos = FVector(radius * FMath::Cos(CurrentValueInRadians) + NewLoc.X, radius * FMath::Sin(CurrentValueInRadians) + NewLoc.Y, CurrentLoc.Z + NewLoc.Z);

        float angle = DeltaTime * 2;


        //formulas to rotate the point arount a center of rotation
        newPos.X = ((CurrentLoc.X - CenterLoc.X) * FMath::Cos(angle)) - ((CurrentLoc.Y - CenterLoc.Y) * FMath::Sin(angle))  + CenterLoc.X;
        newPos.Y = ((CurrentLoc.Y - CenterLoc.Y) * FMath::Cos(angle)) + ((CurrentLoc.X- CenterLoc.X) * FMath::Sin(angle))+ CenterLoc.Y;
        newPos.Z = CurrentLoc.Z;



        ///newPos.X = FMath::Clamp<float>(newPos.X, previousPos.X -15, previousPos.X+15);
       // newPos.Y= FMath::Clamp<float>(newPos.Y, previousPos.Y - 15, previousPos.Y + 15);

    if (ToggleRevolution  && MovementInput.IsZero()) {







        //cube facing the spehre
        FRotator NewRotation =  FRotator(0, IncreasingAngle, 0);

        FQuat QuatRotation = FQuat(NewRotation);// *FQuat(FRotator(GetActorRotation().Pitch, 0, 0));
        
        //AddActorLocalRotation(FRotator(0.f, FMath::RadiansToDegrees<float>(angle), 0.f));
        AddActorWorldRotation(FRotator(0.f, FMath::RadiansToDegrees<float>(angle), 0.f));



        SetActorLocation(newPos, false, 0, ETeleportType::None);

        


       // GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, FString::Printf(TEXT("angolorot %f"), IncreasingAngle));
    }
        
    if (!MovementInput.IsZero())
    {

        //MovementInput = MovementInput.GetSafeNormal() * 100.0f;
        MovementInput *= 30.0f;
        FVector NewLocation = GetActorLocation();
        NewLocation += FVector(MovementInput.X * DeltaTime, MovementInput.Y * DeltaTime ,0.0f);
        SetActorLocation(NewLocation);

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
   
    //AddActorLocalOffset(FVector(0.f, amount, 0.f));


    MovementInput.Y = amount ;//FMath::Clamp<float>(amount, -1.0f, 1.0f);

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

         // InputComponent->BindAction("checkHorizontalMovement", IE_Pressed, this, &AActorCube::checkHorizontalMovPressed);
        //  InputComponent->BindAction("checkHorizontalMovement", IE_Released, this, &AActorCube::checkHorizontalMovReleased);



       InputComponent->BindAxis("MoveForward", this, &AActorCube::MoveForward);
          InputComponent->BindAxis("MoveRight", this, &AActorCube::MoveRight);
        // etc...

        // Now hook up our InputComponent to one in a Player
        // Controller, so that input flows down to us
        EnableInput(GetWorld()->GetFirstPlayerController());
    }    
}

