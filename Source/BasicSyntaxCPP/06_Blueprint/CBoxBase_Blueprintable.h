#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Blueprintable.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_Blueprintable : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeBodyColor(FLinearColor InColor);

	UFUNCTION(BlueprintNativeEvent)
	void ResetBodyColor();

private:
	UFUNCTION()
	void BeginOverlap(AActor* OverrappedActor, AActor* OtherActor);

	UFUNCTION()
	void EndOverlap(AActor* OverrappedActor, AActor* OtherActor);
};
