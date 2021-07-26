// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWndTitle.generated.h"


DECLARE_MULTICAST_DELEGATE(FDraggingEventSignature)

UCLASS()
class MYACTIONRPG_API UDraggableWndTitle : public UUserWidget
{
	GENERATED_BODY()

public:
	// �巡���� ���۵� �� ȣ��Ǵ� �븮��
	FDraggingEventSignature OnDraggingStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title Text")
	FText TitleText;

private:
	// �巡�� ������ ��Ÿ��
	UPROPERTY()
	bool bIsDragging;

	// �巡�� ��ų ������ ��Ÿ��
	UPROPERTY()
	UUserWidget* TargetWidget;

private:
	// �巡���� üũ�� ��ư
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Draggable;

	// â �ݱ� ��ư
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Close;

	// â Ÿ��Ʋ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Title;

	// ���� �Է� ��ġ�� ������ ����
	FVector2D PrevInputPosition;

	// ������ ���� ��ġ�� ������ ����
	FVector2D PrevWidgetPostion;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


private:
	// ���� �巡�׸� ����
	void DragWidget();

private:
	UFUNCTION()
	void OnWidgetDragStarted();

	UFUNCTION()
	void OnWidgetDragFinished();

public:
	void SetTitleTexT(FText newTitleText);

	FORCEINLINE void SetTargetWidget(UUserWidget* targetWidget)
	{
		TargetWidget = targetWidget;
	}

	FORCEINLINE class UButton* GetCloseButton() const
	{
		return Button_Close;
	}
};
