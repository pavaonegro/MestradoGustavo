// Fill out your copyright notice in the Description page of Project Settings.


#include "CSVWriter.h"

#include "Misc/FileHelper.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

UCSVWriter::UCSVWriter()
{
	FString FullPath = FPaths::ProjectContentDir() / "NextTestNumber.txt";

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPath))
	{
		IFileHandle* FileHandle = FPlatformFileManager::Get().GetPlatformFile().OpenWrite(*FullPath);
		if (FileHandle)
		{
			// Write the number zero to the file
			FString ZeroString = FString::Printf(TEXT("0"));
			FileHandle->Write((const uint8*)ZeroString.GetCharArray().GetData(), ZeroString.Len());
			delete FileHandle;
		}
	}
}

void UCSVWriter::SetCsvFileName(FString fileNameChosen)
{
	fileName = fileNameChosen;
}

void UCSVWriter::AddToCsv(int gabarito, int resposta)
{
	tPosition.Add(gabarito);
	aPosition.Add(resposta);

	if (tPosition.Num() >= 1)
	{
		WriteToCsv();
		tPosition.Empty();
		aPosition.Empty();
	}
}

void UCSVWriter::WriteToCsv()
{
	FString FullPath = FPaths::ProjectContentDir() / "NextTestNumber.txt";
	IFileHandle* FileHandle = FPlatformFileManager::Get().GetPlatformFile().OpenRead(*FullPath, false);
	if (FileHandle)
	{
		FString FileContents;
		FFileHelper::LoadFileToString(FileContents, *FullPath);
		fileName = "Teste" + FileContents;

		int32 OutValue = FCString::Atoi(*FileContents);

		// Increment the value
		OutValue++;

		delete FileHandle;

		FileHandle = FPlatformFileManager::Get().GetPlatformFile().OpenWrite(*FullPath);

		// Save the updated value back to the file
		FString NumberString = FString::Printf(TEXT("%d"), OutValue);
		FileHandle->Write((const uint8*)NumberString.GetCharArray().GetData(), NumberString.Len());

		delete FileHandle;
	}


	fileName += ".csv";
	std::ofstream file;
	file.open(TCHAR_TO_UTF8(*(FPaths::ProjectContentDir() + fileName)));

	if (!file.is_open())
	{
		//std::cout << "Nao deu" << "\n";
		return;
	}
	else
	{
		file << "Gabarito ; Respostas" << "\n";
		for (int i = 0; i < tPosition.Num(); i++)
		{
			file << tPosition[i] << ";" << aPosition[i] << ";";

			if (tPosition[i] == aPosition[i]) file << "Acertou";
			else file << "Errou";

			file << "\n";
		}
	}

	file.close();
}
