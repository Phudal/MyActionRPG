// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/CommandLog/CommandLog.h"

void FCommandLog::AddLog(FString commandString, ECommandLog::Type commandLogType)
{
	CommandString.Add(commandString);
	CommandLogType.Add(commandLogType);
}
