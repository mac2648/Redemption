// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadBody.h"
#include "InteractWidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "ChangePowerUpWidget.h"

// Sets default values
ADeadBody::ADeadBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body Mesh"));

	InteractComp = CreateDefaultSubobject<UInteractWidgetComponent>(TEXT("Interact Comp"));

	BoxComp = InteractComp->GetBoxComp();
	BoxComp->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FClassFinder<UUserWidget> PowerUpWidgetFinder(TEXT("/Game/UI/BP_ChangePowerUpWidget"));
	if (PowerUpWidgetFinder.Succeeded())
	{
		ChangePowerUpWidgetClass = PowerUpWidgetFinder.Class;
	}
}

// Called when the game starts or when spawned
void ADeadBody::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeadBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BoxComp->SetWorldLocation(GetActorLocation());
}

void ADeadBody::CreateChangePowerUpWidget()
{
	if (ChangePowerUpWidgetClass)
	{
		UChangePowerUpWidget* PowerUpWidget = CreateWidget<UChangePowerUpWidget>(GetWorld(), ChangePowerUpWidgetClass);
		PowerUpWidget->AddToViewport();
	}
}