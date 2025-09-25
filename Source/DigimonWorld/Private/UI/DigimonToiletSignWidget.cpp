// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DigimonToiletSignWidget.h"

void UDigimonToiletSignWidget::OnToiletSignAnimFinished()
{
	StopAndCleanupAnimation();
	OnToiletSignAnimationEnd.Broadcast();
}

void UDigimonToiletSignWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDigimonToiletSignWidget::NativeDestruct()
{
	StopAndCleanupAnimation();
	Super::NativeDestruct();
}

void UDigimonToiletSignWidget::PlayToiletAnimation()
{
	if (AnimationFinishedDelegate.IsBound())
		return;
	
	if (DisplayAnimation)
	{
		AnimationFinishedDelegate.BindUFunction(this, FName("OnToiletSignAnimFinished"));
		PlayAnimation(DisplayAnimation);
		BindToAnimationFinished(DisplayAnimation, AnimationFinishedDelegate);
	}
}

void UDigimonToiletSignWidget::StopAndCleanupAnimation()
{
	if (DisplayAnimation && AnimationFinishedDelegate.IsBound())
	{
		UnbindFromAnimationFinished(DisplayAnimation, AnimationFinishedDelegate);
		AnimationFinishedDelegate.Unbind();
	}
}
