#include "SkullNPC.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

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
        FText CurrentDialogue = Dialogues[TalkIndex];
        SetDialogueText(CurrentDialogue);

        int32 NumLetters = CurrentDialogue.ToString().Len();
        int32 NumSounds = NumLetters / 3; // Play a sound every 3 letters

        GetWorldTimerManager().ClearTimer(SoundTimerHandle); // Clear any existing timer

        PlayNextSound(0, NumSounds); // Start playing the sounds
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

void ASkullNPC::PlayNextSound(int32 CurrentSoundIndex, int32 TotalSounds)
{
    if (CurrentSoundIndex < TotalSounds)
    {
        if (XyloSounds != nullptr)
        {
            float RandomPitch = FMath::RandRange(0.5f, 1.5f);
            UGameplayStatics::PlaySoundAtLocation(this, XyloSounds, GetActorLocation(), FRotator::ZeroRotator, 1.0f, RandomPitch);
        }

        // Schedule the next sound playback after a delay
        GetWorldTimerManager().SetTimer(SoundTimerHandle, [this, CurrentSoundIndex, TotalSounds]()
            {
                PlayNextSound(CurrentSoundIndex + 1, TotalSounds);
            }, 0.14f, false);
    }
}

void ASkullNPC::OnPlayerDeath()
{
    GetWorldTimerManager().ClearTimer(SoundTimerHandle); 

    if (DialogueWidget)
    {
        DialogueWidget->RemoveFromParent(); 
        DialogueWidget = nullptr; 
    }

    ResetDialogue();
}
