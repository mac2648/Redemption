#include "StaminaBarWidget.h"
#include "Components/ProgressBar.h"


void UStaminaBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EnergyBar->SetFillColorAndOpacity(FullStamina);

	FullStamina = FColor(180.0, 93.0, 161.0, 210.0);
	LowStamina = FColor(217.0, 91.0, 154.0, 210.0);
}

void UStaminaBarWidget::SetBarValuePercent(float const Value)
{
	EnergyBar->SetPercent(Value);

	if (Value <= 0.20)
	{
		EnergyBar->SetFillColorAndOpacity(LowStamina);
	}
	else
	{
		EnergyBar->SetFillColorAndOpacity(FullStamina);
	}

}
