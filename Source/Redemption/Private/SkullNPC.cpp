#include "SkullNPC.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidgetComponent.h"

// Sets default values
ASkullNPC::ASkullNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractComp = CreateDefaultSubobject<UInteractWidgetComponent>(TEXT("InteractComponent"));
	SkullMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkullMeshComponent"));

	SetRootComponent(SkullMeshComp);
}

// Called when the game starts or when spawned
void ASkullNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkullNPC::Talk()
{
	IsTalking = true;

	TalkIndex++;

	if (DialogueWidgetClass != nullptr && DialogueWidget == nullptr)
	{
		DialogueWidget = CreateWidget<UUserWidget>(GetWorld(), DialogueWidgetClass);
		if (DialogueWidget != nullptr)
		{
			DialogueWidget->AddToViewport();
		}
	}

	if (TalkIndex < Dialogues.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Dialogues[TalkIndex]);
		SetDialogueText(Dialogues[TalkIndex]);
	}
	else
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
}

void ASkullNPC::ResetDialogue()
{
	TalkIndex = -1;
	IsTalking = false;

	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
}


// Called every frame
void ASkullNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

