// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ScriptEntryObject.h"

TArray<FString> UWJ_ScriptEntryObject::GetScripts()
{
	return Scripts;
}

void UWJ_ScriptEntryObject::SetScripts(TArray<FString> NewScripts)
{
	Scripts = NewScripts;
}
