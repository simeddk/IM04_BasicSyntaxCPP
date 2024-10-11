#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBall.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class BASICSYNTAXCPP_API ACBall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBall();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComps[3];

private:
	void Drop(int32 InIndex, FLinearColor InColor);

private:
	FVector OriginLocations[3];
	UMaterialInstanceDynamic* DynamicMaterials[3];

	float Pi;
};
