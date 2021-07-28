#include "Widget/ClosableWnd/DraggableWndTitle/DraggableWndTitle.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void UDraggableWndTitle::NativePreConstruct()
{
	Super::NativePreConstruct();
	Text_Title->SetText(TitleText);
}

void UDraggableWndTitle::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Draggable->OnPressed.AddDynamic(this, &UDraggableWndTitle::OnWidgetDragStarted);
	Button_Draggable->OnReleased.AddDynamic(this, &UDraggableWndTitle::OnWidgetDragFinished);
}

void UDraggableWndTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	DragWidget();
}

void UDraggableWndTitle::DragWidget()
{
	// �巡�� ���� �ƴ϶�� �������� ����
	if (!bIsDragging)
		return;

	// �̵���ų ������ �������� �ʴ´ٸ� �������� ����
	if (!IsValid(TargetWidget))
		return;

	auto mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	auto targetSlot = Cast<UCanvasPanelSlot>(TargetWidget->Slot);

	// ������ ��ġ�� ������
	targetSlot->SetPosition(
		PrevWidgetPostion + (mousePosition - PrevInputPosition));

	PrevInputPosition = mousePosition;
	PrevWidgetPostion = targetSlot->GetPosition();
}

void UDraggableWndTitle::OnWidgetDragStarted()
{
	// �̵���ų ������ �������� �ʴ´ٸ� �������� ����
	if (!IsValid(TargetWidget))
		return;

	// �Էµ� ���콺 ��ġ�� ������
	PrevInputPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	/// - UWidgetLayoutLibrary : ���� ���̾ƿ��� ���õ� ��ƿ�� ���� �޼������ �����ϴ� Ŭ����
	/// - GetMousePositionOnViewport : ����Ʈ ���� ���콺 ��ġ�� ��ȯ��
	
	// ������ ���� ��ġ�� ������
	PrevWidgetPostion = Cast<UCanvasPanelSlot>(TargetWidget->Slot)->GetPosition();

	if (OnDraggingStarted.IsBound())
		OnDraggingStarted.Broadcast();

	bIsDragging = true;
}

void UDraggableWndTitle::OnWidgetDragFinished()
{
	// �̵���ų ������ �������� �ʴ´ٸ� �������� ����
	if (!IsValid(TargetWidget))
		return;

	bIsDragging = false;
}

void UDraggableWndTitle::SetTitleTexT(FText newTitleText)
{
	Text_Title->SetText(newTitleText);
}
