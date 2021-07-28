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

	// 해당 객체에 할당된 창 위젯들을 나타냄
	TArray<class UClosableWnd*> AllocatedWnds;

	// 해당 객체에 할당된 창이 아닌 위젯 객체들을 나타냄
	TArray<class UUserWidget*> AllocatedWidgets;

	// 닫힌 창들의 이전 위치를 저장함
	TMap<FString, FVector2D> PrevClosedWndPosition;

private:
	// 창 객체들이 아닌 위젯들이 추가된 캔버스
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WidgetParent;
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WndParent;

public:
	UWidgetControllerWidget(const FObjectInitializer& ObjectInitializer);

	void InitializeWidgetControllerWidget(class ABasePlayerController* basePlayerController);

private:
	// 입력 모드를 초기화함
	/// - 열린 위젯이나, 창이 존재한다면 입력 모드가 초기화하지 않음
	/// - bForceChange : 열린 위젯이나 창의 존재 여부를 무시하고 강제로 초기화 시킬 것인지에 대한 여부를 나타냄
	void ResetInputMode(bool bForceChange = false);

	// 창의 위치를 저장함
	/// - closableWnd : 위치를 저장시킬 창 객체를 전달함
	void SaveWndPosition(const class UClosableWnd* closableWnd);

public:
	// 메시지 박스를 생성함
	/// - titleText : 메시지 박스의 타이틀 문자열을 전달함
	/// - msg : 메시지 박스의 내용을 전달함
	/// - bUseBackGround : 메시지 박스 후면에 어두운 배경이 깔리도록 할 것인지를 결정함
	/// - buttons : 추가될 버튼들을 전달함, EMessageBoxButton 형식을 OR 연산자와 함께 전달해야함
	FORCEINLINE class UMessageBoxWnd* CreateMessageBox(FText titleText, FText msg,
		bool bUseBackground = false, uint8 buttons = 0b00000001);

	// 창의 생성함
	/// - wndClass : 생성할 창 UClass 를 전달함
	/// - bUsePrevPosition : 창의 이전 위치 사용 여부를 전달함
	/// - changeInputMode : 창을 띄운 후 변경할 입력 모드를 전달함
	/// - bShowMouseCursor : 창을 띄운 후 커서를 표시할 것인지를 전달함
	/// - alignmentX : 정렬 기준점이 되는 X 위치를 전달함
	/// - alignmentY : 정렬 기준점이 되는 Y 위치를 전달함
	/// - anchorMinX : 배치 시 기준점이 되는 X 위치를 전달함
	/// - anchorMinY : 배치 시 기준점이 되는 Y 위치를 전달함
	/// - anchorMaxX : 배치 시 기준점이 되는 X 위치를 전달함
	/// - anchorMaxY : 배치 시 기준점이 되는 Y 위치를 전달함
	class UClosableWnd* CreateWnd(TSubclassOf<class UClosableWnd> wndClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float alignmentX = 0.5f, float alignmentY = 0.5f,
		float anchorMinX = 0.5f, float anchorMinY = 0.5f,
		float anchorMaxX = 0.5f, float anchorMaxY = 0.5f);

	// 창을 닫음
	/// - bAllClose : 모든 창을 닫도록 할 것인지에 대한 여부
	/// - closableWndInstanceToClose : 어떤 창을 닫을 건인지 지정함
	///   만약 nullptr 가 전달된다면 마지막에 열었던 창이 닫힘
	void CloseWnd(bool bAllClose = false, class UClosableWnd* closableWndInstanceToClose = nullptr);

	// 창이 아닌 위젯을 추가함
	/// - 추가된 위젯은 CanvasPanel WidgetParent 캔버스 하위로 추가되며,
	///   창 위젯들보다 렌더, 상호작용 우선순위가 낮음
	/// - childWidgetInstance : 하위 위젯으로 추가할 위젯 객체를 전달함
	/// - changeInputMode : 창을 띄운 후 변경할 입력 모드를 나타냄
	/// - bShowMouseCursor : 창을 띄운 후 커서를 표시할 것인지를 나타냄
	/// - width : 띄운 위젯의 너비를 나타냄
	/// - height : 띄운 위젯의 높이를 나타냄
	void AddChildWidget(class UUserWidget* childWidgetInstance,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// 추가시킨 하위 위젯을 닫음
	void CloseChildWidget(class UUserWidget* childWidgetInstance);

	// 창을 최상단으로 설정함
	/// - closableWndInstance : 최상단으로 배치할 창 객체를 전달함
	void SetHighestPriorityWnd(class UClosableWnd* closableWndInstance);

public:
	// 그리드 패널의 요소들을 차례대로 정렬함
	/// - gridPanelElem : 정렬시킬 그리드 패널 요소를 전달함
	/// - maxColumnCount : 최대 행 개수를 전달함
	/// - refCurrentColumnCount : 현재 행 번호를 전달함
	///   전달한 변수의 값은 메서드 내부에서 변경됨
	static void SortGridPanelElem(class UUserWidget* gridPanelElem,
		int maxColumnCount, int& refCurrentColumnCount);
};
