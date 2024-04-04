#include "MovingPlatform.h"
#include "Interactable.h"

#define ACCEPTANCE_DISTANCE 5

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	for (AInteractable* Key : Keys)
	{
		Key->OnActivate.AddDynamic(this, &AMovingPlatform::CheckMoveConditions);
	}

	InitialPos = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AMovingPlatform::CheckMoveConditions()
{
	for (AInteractable* Key : Keys)
	{
		if (!Key->GetIsActive())
		{
			IsMoving = false;
			return;
		}
	}

	IsMoving = true;
}

void AMovingPlatform::Move(float DeltaTime)
{
	if (IsMoving)
	{
		if (!IsGoingBack)
		{
			FVector TargetDirection = (InitialPos + MoveDistance) - GetActorLocation();
			TargetDirection.Normalize();
			FVector NewLocation = GetActorLocation() + TargetDirection * Speed * DeltaTime;

			SetActorLocation(NewLocation);

			if ((InitialPos + MoveDistance - GetActorLocation()).Length() < ACCEPTANCE_DISTANCE)
			{
				if (IsLooping)
				{
					IsGoingBack = true;
				}
				else
				{
					IsMoving = false;
				}
			}
		}
		else
		{
			FVector TargetDirection = InitialPos - GetActorLocation();
			TargetDirection.Normalize();
			FVector NewLocation = GetActorLocation() + TargetDirection * Speed * DeltaTime;

			SetActorLocation(NewLocation);

			if ((NewLocation - InitialPos).Length() < ACCEPTANCE_DISTANCE)
			{
				IsGoingBack = false;
			}
		}
	}
}