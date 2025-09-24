// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/DigimonSettings.h"

const UDigimonSettings* UDigimonSettings::GetDigimonWorldSettings()
{
	return GetDefault<UDigimonSettings>();
}