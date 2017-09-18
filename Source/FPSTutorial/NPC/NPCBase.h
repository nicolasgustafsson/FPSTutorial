// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

UCLASS()
class FPSTUTORIAL_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

private:


public:
	// Sets default values for this character's properties
	ANPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* FirstPersonCamera = nullptr;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class AGunActor> GunClass;

	class AGunActor* Gun = nullptr;

	UFUNCTION(BlueprintCallable)
	void FireWeapon();
};
