// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/BaseCommonUserWidget.h"

void UBaseCommonUserWidget::OnShowAnimFinished()
{
	StopAndCleanupAnimation();
	OnShowAnimationEnd.Broadcast();
}

void UBaseCommonUserWidget::StopAndCleanupAnimation()
{
	if (ShowAnimation && AnimationFinishedDelegate.IsBound())
	{
		UnbindFromAnimationFinished(ShowAnimation, AnimationFinishedDelegate);
		AnimationFinishedDelegate.Unbind();
	}
}

void UBaseCommonUserWidget::NativeDestruct()
{
	StopAndCleanupAnimation();
	Super::NativeDestruct();
}

void UBaseCommonUserWidget::PlayShowAnimation()
{
	if (AnimationFinishedDelegate.IsBound())
		return;
	
	if (ShowAnimation)
	{
		AnimationFinishedDelegate.BindUFunction(this, FName("OnShowAnimFinished"));
		PlayAnimation(ShowAnimation);
		BindToAnimationFinished(ShowAnimation, AnimationFinishedDelegate);
	}
}
