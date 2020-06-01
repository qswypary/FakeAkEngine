/****************************************************************************
 GameHp (header)

 @author qswypary

 ��ʾ��Ϸ������Ѫ���ģ����С����ޡ��͡�ʵ��ֵ�������ԡ�
 �̳��� GameMutableAttribute��
 ����ָ�����������ڰٷֱȱ䶯ʱ�ı��֡�
 ****************************************************************************/
#pragma once
#include "GameMutableAttribute.h"

class GameHp : public GameMutableAttribute {
public:
	// ��ʾֵ�䶯ʱ�ı��ֵ�ö��
	enum Behavior {
		FIXED_ACTUAL_VALUE,		// �̶�ʵ��ֵ
		FIXED_REDUCED_PART,		// �̶�ʵ��ֵ�������޵Ĳ���
		CHANGE_BY_RATIO			// ����������
	};

private:
	double _max_prev;					// ��һ�ε�����ֵ
	double _actual;						// ʵ��ֵ

	Behavior _increase_behavior = CHANGE_BY_RATIO;		// ��������ʱ�ı���
	Behavior _decrease_behavior = CHANGE_BY_RATIO;		// ���޽���ʱ�ı���

public:
	// �����������Ƽ�����ֵ�Ĺ��캯��
	GameHp(const std::string& name, const double& value);

	// ��ȡ����ʵ��ֵ
	double getActualValue() const;

	// ��ȡ��������ʱ�ı���
	Behavior getBehaviorWhenIncrease() const;

	// ��ȡ���޽���ʱ�ı���
	Behavior getBehaviorWhenDecrease() const;

	// ��������ʵ��ֵ���̶�ֵ��
	void addActualValue(double value);

	// ��������ʵ��ֵ���ٷֱȣ�
	void addActualValueByPercent(double percent);

	// ָ����������ʱ�ı���
	void setBehaviorWhenIncrease(Behavior bhv);

	// ָ�����޽���ʱ�ı���
	void setBehaviorWhenDecrease(Behavior bhv);

private:
	// ��д�ĺ���
	// ˢ��
	void refresh();

	// ����ʵ��ֵ
	void adjustActualValue();
};