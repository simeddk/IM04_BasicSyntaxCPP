#include "CPariticles.h"
#include "BasicSyntaxCPP.h"
#include "Particles/ParticleSystem.h"
#include "Components/TextRenderComponent.h"
#include "CBoxBase_Event.h"

ACPariticles::ACPariticles()
{
	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootSceneComp");
	CHelpers::CreateSceneComponent(this, &TextRenderComp, "TextRenderComp", RootSceneComp);

	CHelpers::GetAsset(&Particles[0], "/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Ausar/P_AU_Trap_Impact");
	CHelpers::GetAsset(&Particles[1], "/Game/Explosions/Particles/P_ImpactExplosion4");
	CHelpers::GetAsset(&Particles[2], "/Game/FXVarietyPack/Particles/P_ky_healAura");

	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetTextRenderColor(FColor::Red);
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	TextRenderComp->SetText(GetName());
}

void ACPariticles::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Event::StaticClass(), Actors);

	if (Actors.Num() < 1) return;

	ACBoxBase_Event* Box = Cast<ACBoxBase_Event>(Actors[0]);
	if (Box == nullptr) return;

	Box->OnBoxEvent.AddUFunction(this, "SpawnEmitter");
}

void ACPariticles::SpawnEmitter(int32 InIndex)
{
	ensure(Particles[InIndex]);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorLocation());
}

