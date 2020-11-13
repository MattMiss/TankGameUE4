// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnableState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		//GetPawn()->SetActorTickEnabled(true);
		//GetPawn()->EnableInput(this);
		//GetPawn()
		bShowMouseCursor = true;
	}
	else
	{
		//GetPawn()->SetActorTickEnabled(false);
		//GetPawn()->DisableInput(this);
	}

	//bShowMouseCursor = SetPlayerEnabled;
}
