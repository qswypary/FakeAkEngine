/****************************************************************************
 GameMutableAttribute (header)

 @author qswypary

 �ɱ����Ե��࣬�̳��� GameDoubleAttribute��
 �ں���������Զ�Ӧ�� GameAttributeModifier ����
 ****************************************************************************/
#pragma once
#include <list>
#include "GameAttribute.h"
#include "GameAttributeModifier.h"

class GameMutableAttribute : public GameDoubleAttribute {
private:
	double _final_value = 0.0;                          // ��ԭ���Ժ������޸������������ֵ
	std::list<GameAttributeModifier> _modifiers;        // �����޸����� list

public:
	// �����������ƺ�ֵ�Ĺ��캯��
	GameMutableAttribute(const std::string& name, const double& value);

	// ��д�ĺ���
	// ��ȡ��������������ֵ
	double getValue() const;
	
	// ��ȡ�޸����� list
	std::list<GameAttributeModifier> getModifiers() const;

	// ����޸���
	void addModifier(const GameAttributeModifier& mod);

	// ��������޸���
	void addModifiers(std::list<GameAttributeModifier> modlist);

	// ɾ���޸���
	void deleteModifiers();

protected:
	// ˢ��
	virtual void refresh();

private:
	// ˢ����������ֵ
	void refreshValue();
};