#include "BTTask_CreateStunVFX.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

UBTTask_CreateStunVFX::UBTTask_CreateStunVFX()
{
	NodeName = "Create stun Effect";
}

EBTNodeResult::Type UBTTask_CreateStunVFX::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	ACharacter* OwnerChar = Cast<ACharacter>(BBComp->GetValueAsObject(SelfActor.SelectedKeyName));
	UObject* CurrentEffect = BBComp->GetValueAsObject(StunEffect.SelectedKeyName);

	if (OwnerChar && Effect && (CurrentEffect == nullptr))
	{
		FVector Spawnlocation = OwnerChar->GetActorLocation() + FVector(0, 0, OwnerChar->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

		UNiagaraComponent* NiagaraEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Spawnlocation, FRotator::ZeroRotator, FVector(1, 1, 1), false);
		BBComp->SetValueAsObject(StunEffect.SelectedKeyName, NiagaraEffect);
	}

	return EBTNodeResult::Succeeded;
}