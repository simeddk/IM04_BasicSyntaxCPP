#include "CStaticMeshActorBase.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMeshActorBase::ACStaticMeshActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

}

void ACStaticMeshActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Todo. 동적 머티리얼 에셋 얻어오기 -> DynamicMat화
	StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/StaticMeshes/MI_StaticMesh.MI_StaticMesh'"));

	UMaterialInstanceDynamic::Create(,);
}

void ACStaticMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

