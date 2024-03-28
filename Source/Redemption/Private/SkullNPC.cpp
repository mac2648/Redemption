#include "SkullNPC.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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

		SetDialogueText(Dialogues[TalkIndex]);
		
		
			
		TalkCount = Dialogues[TalkIndex].ToString().Len() / Frequency;
		GetWorld()->GetTimerManager().SetTimer(NhanhaTimer, this,&ASkullNPC::MakeNhanha, 0.2, true);

		
	}
	else
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
		FinishTalk();
		IsTalking = false;
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

void ASkullNPC::MakeNhanha()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundFinder(TEXT("/Game/Assets/Sounds/Characters/Rat/RatAttack_Cue"));
	if (SoundFinder.Succeeded() && TalkCount >= 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundFinder.Object);
		TalkCount -= 1;
	}
}