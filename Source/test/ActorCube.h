// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" 
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h" 
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h" 

#include "ActorCube.generated.h"

class UMaterialInstanceDynamic;



UCLASS()
class IWTEST_API AActorCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorCube();


	UFUNCTION()
	void BindToInput();


	UFUNCTION()
		void LeftClick();

	UFUNCTION()
		void RightClick();
	UFUNCTION()
		void RightClickReleased();

	UFUNCTION()
		void CentralClick();

	UFUNCTION()
		void ResetRotation();





	UFUNCTION()
		void MoveForward(float amount);

	UFUNCTION()
	void MoveRight(float amount);


	UFUNCTION()
		void Revolution();
	UFUNCTION()
		void SelfRotate();
	UFUNCTION()
		void checkHorizontalMovPressed();
		UFUNCTION()
		void checkHorizontalMovReleased();


	UFUNCTION()
	void CustomOnBeginMouseOver(AActor* Actor);

	UFUNCTION()
	void CustomOnEndMouseOver(AActor* Actor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaticMeshComponents)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cubeposition")
	FVector CenterLoc= FVector(0.f,200.f,0.f);

	UStaticMesh* CylinderMesh;
	UStaticMesh* ConeMesh;
	UStaticMesh* CubeMesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsHovered = false;
	bool CanRotate = false;
	bool ToggleSelfRotation = false;
	bool ToggleRevolution = false;
	bool ToggleHorizontalMov = false;
	FVector2D MovementInput;
	FVector newPos;

	float IncreasingAngle = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
	int CentralClickCount;
};
