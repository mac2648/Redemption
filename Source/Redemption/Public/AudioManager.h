#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "AudioManager.generated.h"

UCLASS()
class REDEMPTION_API AudioManager : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AudioManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Function to play a sound at a location
    void PlaySoundEffectAtLocation(USoundCue* SoundCue, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f);

    // Function to play ambient music
    void PlayAmbientMusic();

    // Function to play combat music
    void PlayCombatMusic();

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
};
