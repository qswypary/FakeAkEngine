/****************************************************************************
 GameHp (header)

 @author qswypary

 表示游戏中类似血量的，含有“上限”和“实际值”的属性。
 继承自 GameMutableAttribute。
 可以指定这类属性在百分比变动时的表现。
 ****************************************************************************/
#pragma once
#include "GameMutableAttribute.h"

class GameHp : public GameMutableAttribute {
public:
	// 表示值变动时的表现的枚举
	enum Behavior {
		FIXED_ACTUAL_VALUE,		// 固定实际值
		FIXED_REDUCED_PART,		// 固定实际值不满上限的部分
		CHANGE_BY_RATIO			// 按比例缩放
	};

private:
	double _max_prev;					// 上一次的上限值
	double _actual;						// 实际值

	Behavior _increase_behavior = CHANGE_BY_RATIO;		// 上限提升时的表现
	Behavior _decrease_behavior = CHANGE_BY_RATIO;		// 上限降低时的表现

public:
	// 接受属性名称及上限值的构造函数
	GameHp(const std::string& name, const double& value);

	// 获取属性实际值
	double getActualValue() const;

	// 获取上限提升时的表现
	Behavior getBehaviorWhenIncrease() const;

	// 获取上限降低时的表现
	Behavior getBehaviorWhenDecrease() const;

	// 增加属性实际值（固定值）
	void addActualValue(double value);

	// 增加属性实际值（百分比）
	void addActualValueByPercent(double percent);

	// 指定上限提升时的表现
	void setBehaviorWhenIncrease(Behavior bhv);

	// 指定上限降低时的表现
	void setBehaviorWhenDecrease(Behavior bhv);

private:
	// 重写的函数
	// 刷新
	void refresh();

	// 调整实际值
	void adjustActualValue();
};