// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enum/CommandType.h"

#include "Struct/CommandLog/CommandLog.h"

#include "CommandWidget.generated.h"


UCLASS()
class MYACTIONRPG_API UCommandWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	TSubclassOf<class UCommandLogTextWidget> BP_CommandLogTextWidget;
	class UDataTable* DT_ItemInfo;

private:
	UPROPERTY()
	FCommandLog AddedLogs;

private:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_Input;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox_CommandLogs;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_Logs;

public:
	UCommandWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void AddLog(FString log, ECommandLog::Type logType);
	void AddLog(FText log, ECommandLog::Type logType);

	void ShowDefaultMessage(FString defaultMessage);
	void ShowWarningMessage(FString warningMessage);
	void ShowErrorMessage(FString errorMessage);

	// �Է��� ��ɾ� Ÿ���� ��ȯ�ϴ� �޼���
	/// - inputText : �Է��� ���ڿ��� ������
	ECommand::Type GetCommandType(FString inputText);

private:
	void OnCommandCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
