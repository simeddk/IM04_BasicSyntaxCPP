#include "CAR4.h"
#include "BasicSyntaxCpp.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundCue.h"
#include "CWeaponInterface.h"
#include "CBullet.h"

static TAutoConsoleVariable<bool> CVarDrawDebugLine(TEXT("IM.DrawDebug"), false, TEXT("Visible AR4 aim line"), ECVF_Cheat);

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	CHelpers::GetAsset(&EquipMontage, "/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnequipMontage, "/Game/Character/Animations/AR4/Rifle_Ungrab_Montage");

	CHelpers::GetClass(&ShakeClass, "/Game/AR4/Shake_Fire");
	CHelpers::GetClass(&BulletClass, "/Game/AR4/BP_CBullet");

	CHelpers::GetAsset(&MuzzleEffect, "/Game/Particles_Rifle/Particles/VFX_Muzzleflash");
	CHelpers::GetAsset(&EjectEffect, "/Game/Particles_Rifle/Particles/VFX_Eject_bullet");
	CHelpers::GetAsset(&ImpactEffect, "/Game/Particles_Rifle/Particles/VFX_Impact_Default");
	CHelpers::GetAsset(&FireSound, "/Game/Sounds/S_RifleShoot_Cue");
	CHelpers::GetAsset(&DecalMaterial, "/Game/Materials/M_Decal");

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";

	MontagesPlayRate = 1.75f;
	ShootRange = 10000.f;
}

void ACAR4::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (OwnerCharacter)
	{
		AttachToComponent
		(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			HolsterSocket
		);
	};
	
}

void ACAR4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAiming) return;

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	if (CVarDrawDebugLine.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.f, 0, 3.f);
	}
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		Start,
		End,
		ECC_PhysicsBody,
		QueryParams
	))
	{
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			OwnerInterface->OnTarget();
			return;
		}
	}

	OwnerInterface->OffTarget();
}

void ACAR4::ToggleAutoFiring()
{
	bAutoFiring = !bAutoFiring;
}

void ACAR4::EnableAim()
{
	bAiming = true; 
}

void ACAR4::DisableAim() 
{
	bAiming = false; 
}

void ACAR4::Equip()
{
	if (bEquipped) return;
	if (bPlayingMontage) return;

	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage, MontagesPlayRate);
}

void ACAR4::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket
	);
}

void ACAR4::End_Equip()
{
	bPlayingMontage = false;
}

void ACAR4::Unequip()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;

	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(UnequipMontage, MontagesPlayRate);
}

void ACAR4::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACAR4::End_Unequip()
{
	bPlayingMontage = false;
}

void ACAR4::OnFire()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;

	if (!bAiming) return;
	if (bFiring) return;

	bFiring = true;

	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireTimer, this, &ACAR4::Firing_Internal, 0.1f, true, 0.f);
		return;
	}
	
	Firing_Internal();
}

void ACAR4::OffFire()
{
	bFiring = false;

	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
	}
}

void ACAR4::Firing_Internal()
{
	//Get Aim Ray
	ICWeaponInterface* OwnerInteface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInteface) return;

	FVector Start, End, Direction;
	OwnerInteface->GetAimRay(Start, End, Direction);

	//Camera Shake
	if (!OwnerCharacter) return;
	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();
	if (PC)
	{
		PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
	}

	//Spawn Bullet
	FVector MuzzleLocation =  MeshComp->GetSocketLocation("MuzzleFlash");
	if (BulletClass)
	{
		GetWorld()->SpawnActor<ACBullet>(BulletClass, MuzzleLocation, Direction.Rotation());
	}

	//Play Effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, "MuzzleFlash");
	UGameplayStatics::SpawnEmitterAttached(EjectEffect, MeshComp, "EjectBullet");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation);

	//LineTrace for Visibility
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		Start,
		End,
		ECC_Visibility,
		QueryParams
	))
	{
		FRotator ImpactRotation = Hit.ImpactNormal.Rotation();

		//Spawn Decal
		UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), Hit.ImpactPoint, ImpactRotation, 10.f);
		DecalComp->SetFadeScreenSize(0);

		//Play Impact
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, ImpactRotation);

		//Add Impulse to PhysicsBody
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			Direction = Hit.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 3000.f, OwnerCharacter->GetActorLocation());
		}
	}
}

