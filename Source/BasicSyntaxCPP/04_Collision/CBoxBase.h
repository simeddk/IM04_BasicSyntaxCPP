#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoxBase.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoxBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;

};
