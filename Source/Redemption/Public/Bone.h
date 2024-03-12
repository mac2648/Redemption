// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bone.generated.h"

class UBoxComponent;
class URotatingMovementComponent;

UCLASS()
class REDEMPTION_API ABone : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BoneMesh;

	UPROPERTY(EditAnywhere)
	URotatingMovementComponent* RotationComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SoundWaveClass;

	TArray<AActor*> SoundWave;

public:	
	// Sets default values for this actor's properties
	ABone();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* GetMesh() { return BoneMesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//function created to be able to use timers. it just destroys the bone
	void DestroyBone() { Destroy(); }

	void DestroySoundWave() { SoundWave[0]->Destroy(); SoundWave.RemoveAt(0); }
};
