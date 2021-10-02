// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" 
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h" 
#include "MyPawn.h"


#include "ActorSphere.generated.h"

class UMaterialInstanceDynamic;



UCLASS()
class TEST_API AActorSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorSphere();


	UFUNCTION()
		void BindToInput();




	UFUNCTION()
		void RightClick();
	UFUNCTION()
		void RightClickReleased();
	UFUNCTION()
		void Zoom(float amount);



	UFUNCTION()
		void CustomOnBeginMouseOver(AActor* Actor);

	UFUNCTION()
		void CustomOnEndMouseOver(AActor* Actor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StaticMeshComponents)
		UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category = Movement)
		float AngleAxis;

	UStaticMesh* SphereMesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsHovered = false;
	bool CanRotate = false;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
