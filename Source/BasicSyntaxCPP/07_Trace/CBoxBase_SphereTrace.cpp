#include "CBoxBase_SphereTrace.h"
#include "BasicSyntaxCpp.h"
#include "CSphereTrace.h"

void ACBoxBase_SphereTrace::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSphereTrace::StaticClass(), Actors);
	if (Actors.Num() < 1) return;

	ACSphereTrace* SphereTraceObject = Cast<ACSphereTrace>( Actors[0]);
	if (SphereTraceObject)
	{
		OnActorBeginOverlap.AddDynamic(SphereTraceObject, &ACSphereTrace::BeginOverlap);
	}
}