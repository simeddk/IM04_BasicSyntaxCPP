#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAR4.generated.h"

class UAnimMontage;
class ACharacter;
class ACBullet;
class UParticleSystem;
class USoundCue;

UCLASS()
class BASICSYNTAXCPP_API ACAR4 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAR4();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsPlayingMontage() { return bPlayingMontage; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFiring() { return bAutoFiring; }
	void ToggleAutoFiring();

	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }
	FORCEINLINE float GetShootRange() { return ShootRange; }

	void EnableAim();
	void DisableAim();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

public:
	void OnFire();
	void OffFire();

private:
	UFUNCTION()
	void Firing_Internal();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	float MontagesPlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Range")
	float ShootRange;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> ShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* EjectEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UMaterial* DecalMaterial;

private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bPlayingMontage;
	bool bAiming;
	bool bFiring;
	bool bAutoFiring;

	FTimerHandle AutoFireTimer;
};
