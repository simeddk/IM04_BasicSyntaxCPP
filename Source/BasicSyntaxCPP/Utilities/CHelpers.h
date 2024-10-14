#pragma once

#include "CoreMinimal.h"

class CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutAsset, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		ensureMsgf(Asset.Succeeded(), TEXT("Asset not found"));

		*OutAsset = Asset.Object;
	}

	template<typename T>
	static void CreateSceneComponent(AActor* InObject, T** OutComp, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComp = InObject->CreateDefaultSubobject<T>(InName);

		if (InParent)
		{
			(*OutComp)->SetupAttachment(InParent);
			return;
		}
		
		InObject->SetRootComponent(*OutComp);
		
	}
};