// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSVWriter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MESTRADO_PRESET_API UCSVWriter : public UObject
{
	GENERATED_BODY()
	
public:
	UCSVWriter();

	UFUNCTION(BlueprintCallable, Category = "CSVWriter")
	void SetCsvFileName(FString fileNameChosen);

	UFUNCTION(BlueprintCallable, Category = "CSVWriter")
	void AddToCsv(int gabarito, int resposta);

	//UFUNCTION(BlueprintCallable, Category = "CSVWriter")
	void WriteToCsv();
private:
	TArray<int> tPosition{};
	TArray<int> aPosition{};
	FString fileName;
};
