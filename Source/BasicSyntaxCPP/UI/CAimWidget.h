#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CAimWidget.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCAimWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Dot image to red color
	UFUNCTION(BlueprintImplementableEvent)
	void OnTarget();

	//Dot image to white color
	UFUNCTION(BlueprintImplementableEvent)
	void OffTarget();
};
