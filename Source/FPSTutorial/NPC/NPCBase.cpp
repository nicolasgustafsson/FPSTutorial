// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Camera/CameraComponent.h"
#include "GunActor.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->bUsePawnControlRotation = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(FirstPersonCamera);


	SkeletalMesh->SetOnlyOwnerSee(true);
	SkeletalMesh->bCastDynamicShadow = false;
	SkeletalMesh->CastShadow = false;

}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	if (!GunClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Gun Type attached!"));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGunActor>(GunClass);


	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(SkeletalMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->FirstPersonAnimInstance = SkeletalMesh->GetAnimInstance();
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->ThirdPersonAnimInstance = GetMesh()->GetAnimInstance();
	}

	FirstPersonCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	SkeletalMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	SkeletalMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	
	if (InputComponent)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &ANPCBase::FireWeapon);
	}
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ANPCBase::UnPossessed()
{
	Super::UnPossessed();

	if (Gun && GetMesh())
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

void ANPCBase::FireWeapon()
{
	if (Gun)
	{
		Gun->FireWeapon();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No gun attached to actor %s"), *GetName());
	}
}

