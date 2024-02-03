#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AudioManager::AudioManager()
{
    // Set this actor to call Tick() every frame if you need it. You can turn this off to improve performance if you don't need it.
    // PrimaryActorTick.bCanEverTick = true;

    // Initialize the MusicComponent and set it to not auto-activate
    MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
    MusicComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AudioManager::BeginPlay()
{
    Super::BeginPlay();

    // Start playing the ambient music immediately if it's set
    PlayAmbientMusic();
}

// Implementation of PlaySoundEffectAtLocation
void AudioManager::PlaySoundEffectAtLocation(USoundCue* SoundCue, FVector Location, float VolumeMultiplier, float PitchMultiplier)
{
    if (SoundCue != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SoundCue, Location, VolumeMultiplier, PitchMultiplier);
    }
}

// Implementation to start playing ambient music
void AudioManager::PlayAmbientMusic()
{
    if (AmbientMusicCue != nullptr)
    {
        MusicComponent->SetSound(AmbientMusicCue);
        MusicComponent->Play();
    }
}

// Implementation to switch to combat music
void AudioManager::PlayCombatMusic()
{
    if (CombatMusicCue != nullptr)
    {
        MusicComponent->SetSound(CombatMusicCue);
        MusicComponent->Play();
    }
}
