// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/SkillRangeInfo/SkillRangeInfo.h"

#include "MyActionRPG.h"

FSkillRangeInfo::FSkillRangeInfo()
{
	bUseSphereTrace = true;
	TraceDirection = ESkillRangeDirection::Forward;
	TraceDistance = 200.0f;
	TraceRadius = 50.0f;
	CreateDelay = 0.15f;
}

FVector FSkillRangeInfo::GetTraceDirection(AActor* basedActor)
{
	switch (TraceDirection)
	{
	case ESkillRangeDirection::Forward:
		return basedActor->GetActorForwardVector();
		
	case ESkillRangeDirection::Right:
		return basedActor->GetActorRightVector();
		
	case ESkillRangeDirection::Backward:
		return basedActor->GetActorForwardVector() * -1.0f;
		
	case ESkillRangeDirection::Left:
		return basedActor->GetActorRightVector() * -1.0f;
		
	default:
		return FVector::ZeroVector;
	}
}

TTuple<int32, float> FSkillRangeInfo::GetSkillCalcFormulaResult()
{
	// Queue �� ����� ����� ���
	// ���� �÷��̾��� ���ݷ��� 150

	if (DamageCalcFormula.IsEmpty())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("FSkillRangeInfo.cpp :: %d LINE :: DamageCalcFormula is Empty! (DamageCalcFormula = %s)"),
			__LINE__, *DamageCalcFormula);

		return MakeTuple(1, 0.0f);
	}

	// ���� �÷��̾� ���ݷ��� ��Ÿ��. (�׽�Ʈ��)
	float atk = 150.0f;

	float result = 0;
	/// �ƹ��͵� �ۼ����� �ʾ��� ��� or H1 �� �ۼ��� ��� Ÿ�� Ƚ���� 1 �� �����մϴ�.
	/// H2 -> 2 ȸ Ÿ��
	/// H3 -> 3 ȸ Ÿ��
	/// H4 -> 4 ȸ Ÿ��
	/// H5 -> 5 ȸ Ÿ��
	/// ...
	/// H999 -> 999 ȸ Ÿ��
	/// 
	/// result = 200;
	/// result += (150 * 300%);
	/// result += (150 * 3)
	/// result -= 10;
	/// result *= 3;
	/// result = 3270
	
	// ���� ��� ���
	const uint8 defaultType =		0b00000000;
	const uint8 addition =			0b00000001;
	const uint8 subtraction =		0b00000010;
	const uint8 multiplication =	0b00000100;
	const uint8 division =			0b00001000;

	// ���� �����͵��� ��Ÿ��
	/// - TTuple<���� ���, ��ġ ������>
	TQueue<TTuple<uint8, FString>> calcSeq;

	// ���� ����� ��Ÿ���� ���� ����
	uint8 calcType = defaultType;

	// ��ġ�� ��Ÿ���� ���� ����
	FString calcValue;

	// Ÿ�� Ƚ��
	//// - �� ���� 0 �̶�� Ÿ�� Ƚ���� �д� ���·� �νĽ�Ŵ
	int32 numberOfHits = 1;

	// ���� �о� ���� �����͸� ������
	for (int32 i = 0; i < DamageCalcFormula.Len() + 1; ++i)
	{
		// ��� ���ڿ��� �о��ٸ� ���������� �����͸� �߰���
		if (i == DamageCalcFormula.Len())
		{
			// �ϳ��� �����͸� ť�� �߰���
			calcSeq.Enqueue(MakeTuple(calcType, calcValue));
			break;
		}

		// ���� �ϳ��� ����
		TCHAR read = DamageCalcFormula[i];

		// ������ �о��ٸ� �ϳ��� �������� ������ �ν�
		if (read == TEXT(' '))
		{
			// Ÿ�� Ƚ���� ��� �о��ٸ�
			if (numberOfHits == 0)
			{
				// Ÿ�� Ƚ���� ������
				numberOfHits = FCString::Atoi(*calcValue);
				if (numberOfHits <= 0)
					numberOfHits = 1;

				// Ÿ�� Ƚ���� 0 ������ ������ ������ �� ������ ��
				calcValue = nullptr;
			}

			else if (!calcValue.IsEmpty())
			{
				// �ϳ��� �����͸� ť�� �߰�
				calcSeq.Enqueue(MakeTuple(calcType, calcValue));

				// ���� ���, �����͸� ���
				calcType = defaultType;
				calcValue = nullptr;
			}
		}

		// Ÿ�� Ƚ��
		else if (read == TEXT('h') || read == TEXT('H'))
			numberOfHits = 0;

		// ��� ������
		else if (read == TEXT('+'))
			calcType = addition;
		else if (read == TEXT('-'))
			calcType = subtraction;
		else if (read == TEXT('*'))
			calcType = multiplication;
		else if (read == TEXT('/'))
			calcType = division;

		// ������ ������ �߰�
		else 
			calcValue += read;
	}

	// ������
	TTuple<uint8, FString> calcData;
	while (!calcSeq.IsEmpty())
	{
		calcSeq.Dequeue(calcData);

		// ���� ����� ����
		calcType = calcData.Get<0>();

		// ��ġ ���ڿ��� ����
		calcValue = calcData.Get<1>();

		// str �� ���� ��꿡 ���Ǵ� ��ġ�� ��ȯ��
		Func(float, fnToValue, (FString)) = [](FString str)
		{
			// ��ġ �����Ͱ� �ƴ϶�� ù ��° ���ڸ� ������
			/// - ex) M3 -> 3
			/// - ex) P300 -> 300
			if (!str.IsNumeric())
				str.RemoveAt(0);
			return FCString::Atof(*str);
		};

		// ���� ��꿡 ���Ǵ� ��ġ �����͸� ��Ÿ��
		float value = 0.0f;

		// �ۼ�Ʈ �����
		if (calcValue.Contains(TEXT("p")))
			value = atk * 0.01f * fnToValue(calcValue);

		// �⺻ ���ݷ� * N
		else if (calcValue.Contains(TEXT("d"))) 
			value = atk * fnToValue(calcValue);

		// ��ġ ���
		else
			value = FCString::Atof(*calcValue);

		switch (calcType)
		{
		case defaultType:
			result = value;
			break;
		case addition:
			result += value;
			break;
		case subtraction:
			result -= value;
			break;
		case multiplication:
			result *= value;
			break;
		case division:
			result /= value;
			break;
		}
	}

	return MakeTuple(numberOfHits, result);
}
