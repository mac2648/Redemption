#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

class UAudioComponent;
class USoundCue;
UCLASS()
class REDEMPTION_API AAudioManager : public AActor
{
    GENERATED_BODY()
private:
    // Audio component to play music
    UPROPERTY(VisibleAnywhere, Category = "Audio")
    UAudioComponent* MusicComponent;


    // SoundCue for ambient music
    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundCue* AmbientMusicCue;

    // SoundCue for combat music
    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundCue* CombatMusicCue;

    // Audio component for a radom looping ambient sound
    UPROPERTY(VisibleAnywhere, Category = "Audio")
    UAudioComponent* LoopingAmbientSoundComponent;

    // Array of sound cues for random ambient sounds
    UPROPERTY(EditAnywhere, Category = "Audio")
    TArray<USoundCue*> RandomAmbientSoundCues;
    UPROPERTY(EditAnywhere, Category = "Audio")
    TArray<class APatrolPathIndicator*> RandCueLocations;

    // Timer handle for playing random ambient sounds
    FTimerHandle RandomSoundTimerHandle;

    bool bIsInCombat = true;
    FTimerHandle MusicDelayTimerHandle;
public:
    // Sets default values for this actor's properties
    AAudioManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    // Function to play a random ambient sound
    UFUNCTION()
    void PlayRandomAmbientSound();

    // Function to start playing looping ambient sound
    void StartLoopingAmbientSound();
public:
    // Function to play a sound at a location
    void PlaySoundEffectAtLocation(USoundCue* SoundCue, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f);

    // Function to play ambient music
    void PlayAmbientMusic();

    // Function to play combat music
    void PlayCombatMusic();

    void StartMusicDelayTimer();

    void ResetCombatState();

    // Function to start random ambient sounds playing
    void StartRandomAmbientSounds();

    FTimerHandle MusicResetTimerHandle;
};
