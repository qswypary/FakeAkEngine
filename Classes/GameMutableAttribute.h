/****************************************************************************
 GameMutableAttribute (header)

 @author qswypary

 可变属性的类，继承自 GameDoubleAttribute。
 内含了与该属性对应的 GameAttributeModifier 对象。
 ****************************************************************************/
#pragma once
#include <list>
#include "GameAttribute.h"
#include "GameAttributeModifier.h"

class GameMutableAttribute : public GameDoubleAttribute {
private:
	double _final_value = 0.0;                          // 由原属性和属性修改器算出的最终值
	std::list<GameAttributeModifier> _modifiers;        // 属性修改器的 list

public:
	// 接受属性名称和值的构造函数
	GameMutableAttribute(const std::string& name, const double& value);

	// 重写的函数
	// 获取计算后的最终属性值
	double getValue() const;
	
	// 获取修改器的 list
	std::list<GameAttributeModifier> getModifiers() const;

	// 添加修改器
	void addModifier(const GameAttributeModifier& mod);

	// 批量添加修改器
	void addModifiers(std::list<GameAttributeModifier> modlist);

	// 删除修改器
	void deleteModifiers();

protected:
	// 刷新
	virtual void refresh();

private:
	// 刷新属性最终值
	void refreshValue();
};