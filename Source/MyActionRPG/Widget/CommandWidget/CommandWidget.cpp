// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CommandWidget/CommandWidget.h"

#include "Single/GameInstance/RPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/CommandWidget/CommandLogTextWidget/CommandLogTextWidget.h"

#include "Struct/ItemInfo/ItemInfo.h"

#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"


UCommandWidget::UCommandWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UCommandLogTextWidget> BP_COMMAND_LOG_TEXT_WIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/CommandWidget/BP_CommandLogTextWidget.BP_CommandLogTextWidget_C'"));

	if (BP_COMMAND_LOG_TEXT_WIDGET.Succeeded())
		BP_CommandLogTextWidget = BP_COMMAND_LOG_TEXT_WIDGET.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));

	if (DT_ITEM_INFO.Succeeded())
		DT_ItemInfo = DT_ITEM_INFO.Object;
}

void UCommandWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// EditableTextBox �� ���� �Է��̳�, ��Ŀ�� ���� �̺�Ʈ�� �߻����� ��� ȣ���� �޼��带 �����
	EditableTextBox_Input->OnTextCommitted.AddDynamic(this, &UCommandWidget::OnCommandCommitted);

	// Command Widget �� ��Ŀ���� �����ϵ��� ��
	bIsFocusable = true;
	EditableTextBox_Input->SetKeyboardFocus();

	if (GetGameInst(GetWorld())->LoadJson<FCommandLog>(TEXT("CommandLog"), AddedLogs))
	{
		// ���� �Է��� ��� �α׵� �߰�
		for (int32 i = 0; i < AddedLogs.Num(); i++)
		{
			auto logData = AddedLogs[i];
			AddLog(logData.Get<0>(), logData.Get<1>());
		}
	}

	// ��ũ�ѹٸ� ���ϴ����� ����
	ScrollBox_Logs->ScrollToEnd();
}

void UCommandWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GetGameInst(GetWorld())->SaveJson(TEXT("CommandLog"), AddedLogs);
}

void UCommandWidget::AddLog(FString log, ECommandLog::Type logType)
{
	AddLog(FText::FromString(log), logType);
}

void UCommandWidget::AddLog(FText log, ECommandLog::Type logType)
{
	UCommandLogTextWidget* newLogTextWidget = CreateWidget<UCommandLogTextWidget>(this, BP_CommandLogTextWidget);
	VerticalBox_CommandLogs->AddChild(newLogTextWidget);

	newLogTextWidget->SetText(log);
	newLogTextWidget->SetLogLevel(logType);

	// ��ũ�ѹٸ� ���ϴ����� ����
	ScrollBox_Logs->ScrollToEnd();
}

void UCommandWidget::ShowDefaultMessage(FString defaultMessage)
{
	auto logData = MakeTuple(defaultMessage, ECommandLog::Log_Default);

	AddLog(logData.Get<0>(), logData.Get<1>());
	AddedLogs.AddLog(logData.Get<0>(), logData.Get<1>());
}

void UCommandWidget::ShowWarningMessage(FString warningMessage)
{
	auto logData = MakeTuple(warningMessage, ECommandLog::Log_Warning);
	AddLog(logData.Get<0>(), logData.Get<1>());
	AddedLogs.AddLog(logData.Get<0>(), logData.Get<1>());
	LOG(TEXT("%s"), *warningMessage);
}

void UCommandWidget::ShowErrorMessage(FString errorMessage)
{
	auto logData = MakeTuple(errorMessage, ECommandLog::Log_Error);
	AddLog(logData.Get<0>(), logData.Get<1>());
	AddedLogs.AddLog(logData.Get<0>(), logData.Get<1>());
	UE_LOG(LogTemp, Error, TEXT("%s"), *errorMessage);
}

ECommand::Type UCommandWidget::GetCommandType(FString inputText)
{
	if (inputText.Find(TEXT("SpawnItem")) == 0)
		return ECommand::Command_SpawnItem;

	return ECommand::Command_None;
}

void UCommandWidget::OnCommandCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	LOG(TEXT("CommitMethod = %d"), CommitMethod);

	if (CommitMethod == ETextCommit::OnEnter)
	{
		FString commandStr = Text.ToString();

		switch (GetCommandType(commandStr))
		{
		case ECommand::Command_SpawnItem:
		{
			// ���ڿ��� ������ �������� ���� ������ �迭
			TArray<FString> commandArgs;
			commandStr.ParseIntoArray(commandArgs, TEXT(" "));

			// �Է��� ��� ������ �߸��� ���
			if (commandArgs.Num() < 2 || commandArgs.Num() > 3)
			{
				ShowErrorMessage(TEXT("�߸��� ��� : ") + commandStr);
				ShowErrorMessage(TEXT("ex) SpawnItem [ItemCode] [Count]"));
				break;
			}

			// ������ �ڵ�
			FName itemCode = FName(*commandArgs[1]);

			// ������ ���� �ε�
			FString contextString;
			FItemInfo* itemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

			// ������ ������ ã�� ���ߴٸ�
			if (itemInfo == nullptr)
			{
				ShowErrorMessage(TEXT("�߸��� ������ �ڵ� :") + commandArgs[1]);
				break;
			}

			// �߰��� ������ ����
			int32 itemCount = 1;

			// �������� �Է��� ���
			/// - ex) SpawnItem [ItemCode] [ItemCount]
			if (commandArgs.Num() > 2)
				itemCount = FCString::Atoi(*commandArgs[2]);
			/// - Atoi(const TCHAR * string) : string �� int32 �������� ��ȯ�Ͽ� ��ȯ�մϴ�.
			///   ���� ��ȯ �Ұ����� ���ڿ��� ��� 0 �� ��ȯ�մϴ�.

			// �������� ������ ������ �Էµ��� �ʾҴٸ�
			if (itemCount < 1 || itemCount > 1000)
			{
				ShowErrorMessage(TEXT("�߸��� ������ ���� : ") + commandArgs[2]);
				ShowErrorMessage(TEXT("������ ������ 1 ~ 1000 �� ���� ������ �� �ֽ��ϴ�."));
				break;
			}

			// �κ��丮�� ������ �߰�
			/// - ��� �������̶�� ���� �ִ� ������ 1 �̹Ƿ�
			/// - �߰��� ������ �Ͼ �� �ֵ��� �մϴ�.
			if (itemInfo->ItemType == EItemType::Equipment)
			{
				for (int32 i = 0; i < itemCount; i++)
				{
					FItemSlotInfo newItem(itemCode, 1, 1);
					GetManager(UPlayerManager)->GetPlayerInventory()->AddItem(newItem);
				}
			}

			// ��� �������� �ƴ϶��
			else
			{
				int32 maxSlotCount = (itemInfo->MaxSlotCount == 0) ? 1 : itemInfo->MaxSlotCount;
				FItemSlotInfo newItem(itemCode, itemCount, maxSlotCount);
				GetManager(UPlayerManager)->GetPlayerInventory()->AddItem(newItem);
			}
			break;
		}
		case ECommand::Command_None:
		{
			ShowErrorMessage(TEXT("�߸��� ��� : ") + commandStr);
			break;
		}
		}
		EditableTextBox_Input->SetError(FText());
	}
	else if (CommitMethod == ETextCommit::OnCleared)
	{
		EditableTextBox_Input->SetKeyboardFocus();
	}
}
