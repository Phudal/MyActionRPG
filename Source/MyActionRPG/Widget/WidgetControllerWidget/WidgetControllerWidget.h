// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/InputModeType.h"

#include "WidgetControllerWidget.generated.h"


UCLASS()
class MYACTIONRPG_API UWidgetControllerWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	TSubclassOf<class UMessageBoxWnd> BP_MessageBoxWnd;
	TSubclassOf<UUserWidget> BP_MessageBoxBackground;

private:
	class ABasePlayerController* PlayerController;

	// �ش� ��ü�� �Ҵ�� â �������� ��Ÿ��
	TArray<class UClosableWnd*> AllocatedWnds;

	// �ش� ��ü�� �Ҵ�� â�� �ƴ� ���� ��ü���� ��Ÿ��
	TArray<class UUserWidget*> AllocatedWidgets;

	// ���� â���� ���� ��ġ�� ������
	TMap<FString, FVector2D> PrevClosedWndPosition;

private:
	// â ��ü���� �ƴ� �������� �߰��� ĵ����
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WidgetParent;
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WndParent;

public:
	UWidgetControllerWidget(const FObjectInitializer& ObjectInitializer);

	void InitializeWidgetControllerWidget(class ABasePlayerController* basePlayerController);

private:
	// �Է� ��带 �ʱ�ȭ��
	/// - ���� �����̳�, â�� �����Ѵٸ� �Է� ��尡 �ʱ�ȭ���� ����
	/// - bForceChange : ���� �����̳� â�� ���� ���θ� �����ϰ� ������ �ʱ�ȭ ��ų �������� ���� ���θ� ��Ÿ��
	void ResetInputMode(bool bForceChange = false);

	// â�� ��ġ�� ������
	/// - closableWnd : ��ġ�� �����ų â ��ü�� ������
	void SaveWndPosition(const class UClosableWnd* closableWnd);

public:
	// �޽��� �ڽ��� ������
	/// - titleText : �޽��� �ڽ��� Ÿ��Ʋ ���ڿ��� ������
	/// - msg : �޽��� �ڽ��� ������ ������
	/// - bUseBackGround : �޽��� �ڽ� �ĸ鿡 ��ο� ����� �򸮵��� �� �������� ������
	/// - buttons : �߰��� ��ư���� ������, EMessageBoxButton ������ OR �����ڿ� �Բ� �����ؾ���
	FORCEINLINE class UMessageBoxWnd* CreateMessageBox(FText titleText, FText msg,
		bool bUseBackground = false, uint8 buttons = 0b00000001);

	// â�� ������
	/// - wndClass : ������ â UClass �� ������
	/// - bUsePrevPosition : â�� ���� ��ġ ��� ���θ� ������
	/// - changeInputMode : â�� ��� �� ������ �Է� ��带 ������
	/// - bShowMouseCursor : â�� ��� �� Ŀ���� ǥ���� �������� ������
	/// - alignmentX : ���� �������� �Ǵ� X ��ġ�� ������
	/// - alignmentY : ���� �������� �Ǵ� Y ��ġ�� ������
	/// - anchorMinX : ��ġ �� �������� �Ǵ� X ��ġ�� ������
	/// - anchorMinY : ��ġ �� �������� �Ǵ� Y ��ġ�� ������
	/// - anchorMaxX : ��ġ �� �������� �Ǵ� X ��ġ�� ������
	/// - anchorMaxY : ��ġ �� �������� �Ǵ� Y ��ġ�� ������
	class UClosableWnd* CreateWnd(TSubclassOf<class UClosableWnd> wndClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float alignmentX = 0.5f, float alignmentY = 0.5f,
		float anchorMinX = 0.5f, float anchorMinY = 0.5f,
		float anchorMaxX = 0.5f, float anchorMaxY = 0.5f);

	// â�� ����
	/// - bAllClose : ��� â�� �ݵ��� �� �������� ���� ����
	/// - closableWndInstanceToClose : � â�� ���� ������ ������
	///   ���� nullptr �� ���޵ȴٸ� �������� ������ â�� ����
	void CloseWnd(bool bAllClose = false, class UClosableWnd* closableWndInstanceToClose = nullptr);

	// â�� �ƴ� ������ �߰���
	/// - �߰��� ������ CanvasPanel WidgetParent ĵ���� ������ �߰��Ǹ�,
	///   â �����麸�� ����, ��ȣ�ۿ� �켱������ ����
	/// - childWidgetInstance : ���� �������� �߰��� ���� ��ü�� ������
	/// - changeInputMode : â�� ��� �� ������ �Է� ��带 ��Ÿ��
	/// - bShowMouseCursor : â�� ��� �� Ŀ���� ǥ���� �������� ��Ÿ��
	/// - width : ��� ������ �ʺ� ��Ÿ��
	/// - height : ��� ������ ���̸� ��Ÿ��
	void AddChildWidget(class UUserWidget* childWidgetInstance,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// �߰���Ų ���� ������ ����
	void CloseChildWidget(class UUserWidget* childWidgetInstance);

	// â�� �ֻ������ ������
	/// - closableWndInstance : �ֻ������ ��ġ�� â ��ü�� ������
	void SetHighestPriorityWnd(class UClosableWnd* closableWndInstance);

public:
	// �׸��� �г��� ��ҵ��� ���ʴ�� ������
	/// - gridPanelElem : ���Ľ�ų �׸��� �г� ��Ҹ� ������
	/// - maxColumnCount : �ִ� �� ������ ������
	/// - refCurrentColumnCount : ���� �� ��ȣ�� ������
	///   ������ ������ ���� �޼��� ���ο��� �����
	static void SortGridPanelElem(class UUserWidget* gridPanelElem,
		int maxColumnCount, int& refCurrentColumnCount);
};
