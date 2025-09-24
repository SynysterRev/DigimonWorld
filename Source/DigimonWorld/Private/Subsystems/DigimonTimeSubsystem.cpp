// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DigimonTimeSubsystem.h"

void UDigimonTimeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LastHour = FMath::FloorToInt(CurrentTimeOfDay);
	LastMinute = FMath::FloorToInt((CurrentTimeOfDay - LastHour) * 60.0f);
}

TStatId UDigimonTimeSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UDigimonTimeSubsystem, STATGROUP_Tickables);
}

void UDigimonTimeSubsystem::Tick(float DeltaTime)
{
	float GameTimeDelta = DeltaTime * TIME_SCALE;
	CurrentTimeOfDay += GameTimeDelta / 3600.0f;

	// Handle a new day
	if (CurrentTimeOfDay >= 24.0f)
	{
		CurrentTimeOfDay -= 24.0f;
		CurrentDay++;
		OnNewDay.Broadcast(CurrentDay);
	}
    
	int32 NewHour = FMath::FloorToInt(CurrentTimeOfDay);
	int32 NewMinute = FMath::FloorToInt((CurrentTimeOfDay - NewHour) * 60.0f);
    
	if (NewHour != LastHour)
	{
		LastHour = NewHour;
		OnHourChanged.Broadcast(NewHour);
	}
    
	if (NewMinute != LastMinute)
	{
		LastMinute = NewMinute;
		OnMinuteChanged.Broadcast(NewHour, NewMinute);
	}
}
