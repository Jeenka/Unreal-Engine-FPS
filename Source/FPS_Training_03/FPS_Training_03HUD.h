// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_Training_03HUD.generated.h"

UCLASS()
class AFPS_Training_03HUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPS_Training_03HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

