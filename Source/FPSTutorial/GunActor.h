// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class FPSTUTORIAL_API AGunActor : public AActor
{
	GENERATED_BODY()

	/** Gun mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;


public:	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Shooting)
	TSubclassOf<class APeaProjectile> ProjectileClass;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimInstance* AnimInstance;

	// Sets default values for this actor's properties
	AGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireWeapon();

	
};
