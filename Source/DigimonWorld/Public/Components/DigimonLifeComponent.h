// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/DigimonBaseData.h"
#include "DigimonLifeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIGIMONWORLD_API UDigimonLifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDigimonLifeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHourChanged(int32 NewHour);

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 MaxAge;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 Age;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 Weight;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 Life = 3;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 Happiness = 50;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 Discipline = 50;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 VirusGauge = 0;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 CareMistakes = 0;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 BornHour = 6;

public:
	int32 GetAge() const { return Age; }
	int32 GetWeight() const { return Weight; }
	int32 GetLife() const { return Life; }
	int32 GetHappiness() const { return Happiness; }
	int32 GetDiscipline() const { return Discipline; }
	int32 GetVirusGauge() const { return VirusGauge; }
	int32 GetCareMistakes() const { return CareMistakes; }
	
	void InitializeDigimonLife(const FDigimonPartnerData& PartnerData);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void AddCareMistakes(int32 Amount);
	void ResetCareMistakes();
	void AddVirusGauge();
	void ResetVirusGauge();
	void AddDiscipline(int32 Amount);
	void RemoveDiscipline(int32 Amount);
	void SetDiscipline(int32 Amount);
	void AddHappiness(int32 Amount);
	void RemoveHappiness(int32 Amount);
	void SetHappiness(int32 Amount);
	void AddWeight(int32 Amount);
	void RemoveWeight(int32 Amount);
	void SetWeight(int32 Amount);
};
