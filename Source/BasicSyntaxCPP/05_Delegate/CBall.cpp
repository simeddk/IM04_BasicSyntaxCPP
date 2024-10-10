#include "CBall.h"

ACBall::ACBall()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i + 1));

		MeshComps[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(SubObjectName));
		//Todo. y방향으로 2m 건너뛸것
		//MeshComps[i]->
	}
}

void ACBall::BeginPlay()
{
	Super::BeginPlay();
	
}
