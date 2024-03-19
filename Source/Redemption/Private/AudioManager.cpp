#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"


// Constants for random sound intervals, this is in seconds
const float MinRandomSoundInterval = 3.0f; 
const float MaxRandomSoundInterval = 15.0f; 

// Sets default values
AAudioManager::AAudioManager()
{
    // Set this actor to not call Tick() every frame. You can turn this on if you need it.
    PrimaryActorTick.bCanEverTick = false;

    // Initialize the MusicComponent and set it to not auto-activate
    MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
    MusicComponent->bAutoActivate = false;

    // Initialize the LoopingAmbientSoundComponent and set it to not auto-activate
    LoopingAmbientSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopingAmbientSoundComponent"));
    LoopingAmbientSoundComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
    Super::BeginPlay();

    // Start playing the ambient music immediately if it's set
    PlayAmbientMusic();

    // Start playing the looping ambient sound
    if (LoopingAmbientSoundComponent->Sound)
    {
        LoopingAmbientSoundComponent->Play(0.f);
    }

    // Start playing random ambient sounds
    StartRandomAmbientSounds();
}

void AAudioManager::PlayRandomAmbientSound()
{
    int32 RandomIndex = FMath::RandRange(0, RandomAmbientSoundCues.Num() - 1);
    UGameplayStatics::PlaySoundAtLocation(this, RandomAmbientSoundCues[RandomIndex], GetActorLocation());

    // Reset the timer with a new random interval
    float RandomInterval = FMath::RandRange(MinRandomSoundInterval, MaxRandomSoundInterval);
    GetWorld()->GetTimerManager().SetTimer(RandomSoundTimerHandle, this, &AAudioManager::PlayRandomAmbientSound, RandomInterval, false);
}

void AAudioManager::StartRandomAmbientSounds()
{

    // Ensure there's at least one sound cue to play
    if (RandomAmbientSoundCues.Num() > 0)
    {
        // Start a looping timer that calls PlayRandomAmbientSound at random intervals
        float RandomInterval = FMath::RandRange(MinRandomSoundInterval, MaxRandomSoundInterval);
        GetWorld()->GetTimerManager().SetTimer(RandomSoundTimerHandle, this, &AAudioManager::PlayRandomAmbientSound, RandomInterval, false);
    }
}
// Implementation to start playing ambient music
void AAudioManager::PlayAmbientMusic()
{
    if (AmbientMusicCue != nullptr && bIsInCombat)
    {
        bIsInCombat = false;
        MusicComponent->SetSound(AmbientMusicCue);
        MusicComponent->Play();
    }
}

void AAudioManager::PlayCombatMusic()
{
    // Only switch to combat music if we're not already in combat mode
    if (CombatMusicCue != nullptr && !bIsInCombat)
    {
        bIsInCombat = true;
        // Clear any pending switch back to ambient music
        GetWorldTimerManager().ClearTimer(MusicDelayTimerHandle);

        // Set the combat music and play it
        MusicComponent->SetSound(CombatMusicCue);
        MusicComponent->Play();
    }
}

void AAudioManager::StartMusicDelayTimer()
{
    GetWorldTimerManager().SetTimer(MusicDelayTimerHandle, this, &AAudioManager::PlayAmbientMusic, 5.0f, false);
}

void AAudioManager::ResetCombatState()
{
    // Only proceed if we're currently in combat
    if (bIsInCombat)
    {
        // Start or reset the delay timer for switching back to ambient music
        StartMusicDelayTimer();
    }
}