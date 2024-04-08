// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangePowerUpWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionPlayer.h"
#include "PowerUpComponent.h"

void UChangePowerUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BoneButton->OnClicked.AddDynamic(this, &UChangePowerUpWidget::ActivateBonePower);
	ParryButton->OnClicked.AddDynamic(this, &UChangePowerUpWidget::ActivateParryPower);
	HoverButton->OnClicked.AddDynamic(this, &UChangePowerUpWidget::ActivateHoverPower);

	if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPowerUpComp = Player->GetPowerUpComponent();
		if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
		{
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void UChangePowerUpWidget::ActivateBonePower()
{
	PlayerPowerUpComp->ChangeActivePowerUp(EActivePowerUp::BoneThrow);
	Delete();
}

void UChangePowerUpWidget::ActivateParryPower()
{
	PlayerPowerUpComp->ChangeActivePowerUp(EActivePowerUp::Parry);
	Delete();
}

void UChangePowerUpWidget::ActivateHoverPower()
{
	PlayerPowerUpComp->ChangeActivePowerUp(EActivePowerUp::Hover);
	Delete();
}

void UChangePowerUpWidget::Delete()
{
	if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->SetShowMouseCursor(false);
		}
	}

	RemoveFromParent();
}