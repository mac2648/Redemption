#include "CreateQuestionMark.h"
#include "QuestionMarkWidget.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

UCreateQuestionMark::UCreateQuestionMark()
{
	NodeName = "Create Question Mark";
}

EBTNodeResult::Type UCreateQuestionMark::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	ACharacter* OwnerChar = Cast<ACharacter>(BBComp->GetValueAsObject(SelfActor.SelectedKeyName));

	if (!OwnerChar)
	{
		return EBTNodeResult::Failed;
	}

	UQuestionMarkWidget* QuestionMark = Cast<UQuestionMarkWidget>(BBComp->GetValueAsObject(QuestionMarkWidged.SelectedKeyName));

	if (QuestionMark == nullptr)
	{
		if (QuestionMarkWidgetClass)
		{
			QuestionMark = CreateWidget<UQuestionMarkWidget>(GetWorld(), QuestionMarkWidgetClass);
			if (QuestionMark)
			{
				QuestionMark->AddToViewport();
				QuestionMark->SetOwnerActor(OwnerChar, OwnerChar->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
				BBComp->SetValueAsObject(QuestionMarkWidged.SelectedKeyName, QuestionMark);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}