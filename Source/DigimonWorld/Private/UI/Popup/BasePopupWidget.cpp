// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Popup/BasePopupWidget.h"

#include "CommonButtonBase.h"
#include "Input/CommonUIInputTypes.h"

UBasePopupWidget::UBasePopupWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsModal = true;
	bAutoActivate = true;
}

void UBasePopupWidget::OpenPopup()
{
	if (AnimationFinishedDelegate.IsBound())
		return;
	
	if (OpenAnimation)
	{
		AnimationFinishedDelegate.BindUFunction(this, FName("PopupOpened"));
		PlayAnimation(OpenAnimation);
		BindToAnimationFinished(OpenAnimation, AnimationFinishedDelegate);
	}
}

void UBasePopupWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	ConfirmHandle = RegisterUIActionBinding(FBindUIActionArgs(TriggeringInputAction,
		true,
		FSimpleDelegate::CreateUObject(this, &UBasePopupWidget::OnConfirmAction)
	));

	SetIsFocusable(true);
	SetFocus();

	// CancelHandle = RegisterUIActionBinding(FBindUIActionArgs(
	// 	FDataTableRowHandle(, "Cancel"),
	// 	false,
	// 	FSimpleDelegate::CreateUObject(this, &UBasePopupWidget::OnCancelAction)
	// ));
}

void UBasePopupWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
    
	ConfirmHandle.Unregister();
	CancelHandle.Unregister();
}

void UBasePopupWidget::OnConfirmAction()
{
	if (!bInputEnabled) return;
    
	ClosePopup();
}

void UBasePopupWidget::OnCancelAction()
{
	if (!bInputEnabled) return;
    
	ClosePopup();
}

void UBasePopupWidget::ClosePopup()
{
	OnPopupClosed.Broadcast();
    
	DeactivateWidget();
}

void UBasePopupWidget::SetInputEnabled(bool bEnabled)
{
	bInputEnabled = bEnabled;
}

void UBasePopupWidget::PopupOpened()
{
	StopAndCleanupAnimation();
	OnPopupOpened.Broadcast();
}

void UBasePopupWidget::StopAndCleanupAnimation()
{
	if (OpenAnimation && AnimationFinishedDelegate.IsBound())
	{
		UnbindFromAnimationFinished(OpenAnimation, AnimationFinishedDelegate);
		AnimationFinishedDelegate.Unbind();
	}
}
