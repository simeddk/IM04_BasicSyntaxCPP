#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPariticles.generated.h"

class UParticleSystem;
class UTextRenderComponent;

UCLASS()
class BASICSYNTAXCPP_API ACPariticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPariticles();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SpawnEmitter(int32 InIndex);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;

	UPROPERTY(VisibleInstanceOnly)
	UParticleSystem* Particles[3];
};
