// Fill out your copyright notice in the Description page of Project Settings.

#include "GunActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/PeaProjectile.h"
#include "Classes/Kismet/GameplayStatics.h"


// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));


	CurrentCooldown = 0.0f;
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentCooldown -= DeltaTime;
}


bool AGunActor::FireWeapon()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (CanFireWeapon() == true)
			{
				const FRotator ShootDirection = FP_MuzzleLocation->GetComponentRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<APeaProjectile>(ProjectileClass, SpawnLocation, ShootDirection, ActorSpawnParams);

				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}


				UE_LOG(LogTemp, Warning, TEXT("Firing Weapons!"));
				CurrentCooldown = WeaponCooldownTimer;

				if (FirstPersonAnimInstance != nullptr && FireAnimationFirstPerson != nullptr)
				{
					FirstPersonAnimInstance->Montage_Play(FireAnimationFirstPerson, 1.f);

				}
				if (ThirdPersonAnimInstance != nullptr && FireAnimationThirdPerson != nullptr)
				{
					ThirdPersonAnimInstance->Montage_Play(FireAnimationThirdPerson, 1.f);
				}

				return true;
			}
		}
	}

	return false;

	//// try and play a firing animation if specified

}


bool AGunActor::CanFireWeapon()
{
	return CurrentCooldown <= 0.0f;
}

