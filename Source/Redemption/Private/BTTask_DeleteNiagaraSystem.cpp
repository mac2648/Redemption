#include "BTTask_DeleteNiagaraSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

UBTTask_DeleteNiagaraSystem::UBTTask_DeleteNiagaraSystem()
{
	NodeName = "Delete Niagara";
}

EBTNodeResult::Type UBTTask_DeleteNiagaraSystem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UNiagaraComponent* CurrentEffect = Cast<UNiagaraComponent>(BBComp->GetValueAsObject(Effect.SelectedKeyName));

	if (CurrentEffect)
	{
		CurrentEffect->DestroyComponent();
		BBComp->SetValueAsObject(Effect.SelectedKeyName, nullptr);
	}

	return EBTNodeResult::Succeeded;
}