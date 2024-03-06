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
    if (AmbientMusicCue != nullptr)
    {
        MusicComponent->SetSound(AmbientMusicCue);
        MusicComponent->Play();
    }
}

// Implementation to switch to combat music
void AAudioManager::PlayCombatMusic()
{
    if (CombatMusicCue != nullptr)
    {
        MusicComponent->SetSound(CombatMusicCue);
        MusicComponent->Play();
    }
}

void AAudioManager::OnPlayerSpotted()
{
    // Cancel any existing timer to reset the music, ensuring combat music plays for at least 5 seconds
    GetWorld()->GetTimerManager().ClearTimer(MusicResetTimerHandle);

    // Switch to combat music
    PlayCombatMusic();

    // Start a timer to reset the music after 5 seconds
    GetWorld()->GetTimerManager().SetTimer(MusicResetTimerHandle, this, &AAudioManager::ResetAmbientMusic, 5.0f, false);
}

void AAudioManager::ResetAmbientMusic()
{
    // Stop the combat music
    MusicComponent->Stop();

    // Play the ambient music again
    PlayAmbientMusic();
}
