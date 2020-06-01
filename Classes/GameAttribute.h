/****************************************************************************
 GameAttribute (header)

 @author qswypary

 表示游戏中单位的单个属性的类模板。
 ****************************************************************************/
#pragma once
#include <string>
#include <stdexcept>

template <class _Ty>
class GameAttribute {
private:
	// 表示对值大小进行限制的结构体
	struct Bound {
		bool enabled;           // 限制是否起作用
		_Ty value;              // 限制的值
	};

	const std::string _name;    // 属性名称
	_Ty _value;                 // 属性值
	Bound _max = {};            // 属性值上限
	Bound _min = {};            // 属性值下限

public:
	// 接受属性名称和值的构造函数
	GameAttribute(const std::string& name, const _Ty& value);

	// 获取属性名称
	std::string getName() const;

	// 获取属性值
	virtual _Ty getValue() const;

	// 检查给定值是否符合上下限要求
	bool isValid(const _Ty& value) const;

	// 设置上限
	// 可能抛出错误 std::invalid_argument
	void setMax(const _Ty& max);

	// 清除上限
	void clearMax();

	// 设置下限
	// 可能抛出错误 std::invalid_argument
	void setMin(const _Ty& min);

	// 清除下限
	void clearMin();

	// 运算符重载，按值比较
	bool operator==(const GameAttribute& that) const;
	bool operator!=(const GameAttribute& that) const;

protected:
	// 调整给定值
	_Ty adjust(_Ty value) const;

private:
	// 调整超出范围的属性值
	void adjustValue();
};

typedef GameAttribute<bool> GameBoolAttribute;
typedef GameAttribute<int> GameIntAttribute;
typedef GameAttribute<double> GameDoubleAttribute;
typedef GameAttribute<std::string> GameStringAttribute;

template<class _Ty>
inline GameAttribute<_Ty>::GameAttribute(const std::string& name, const _Ty& value) :
	_name(name), _value(value)
{
	_max.enabled = _min.enabled = false;
}

template<class _Ty>
inline std::string GameAttribute<_Ty>::getName() const
{
	return _name;
}

template<class _Ty>
inline _Ty GameAttribute<_Ty>::getValue() const
{
	return _value;
}

template<class _Ty>
inline bool GameAttribute<_Ty>::isValid(const _Ty& value) const
{
	return (!_max.enabled || !(_max.value < value))
		&& (!_min.enabled || !(value < _min.value));
}

template<class _Ty>
inline void GameAttribute<_Ty>::setMax(const _Ty& max)
{
	if (_min.enabled && max < _min.value) {
		throw std::invalid_argument("bad argument; maximum is too small");
	}
	_max.enabled = true;
	_max.value = max;
	adjustValue();
}

template<class _Ty>
inline void GameAttribute<_Ty>::clearMax()
{
	_max.enabled = false;
}

template<class _Ty>
inline void GameAttribute<_Ty>::setMin(const _Ty& min)
{
	if (_max.enabled && _max.value < min) {
		throw std::invalid_argument("bad argument; minimum is too big");
	}
	_min.enabled = true;
	_min.value = min;
	adjustValue();
}

template<class _Ty>
inline void GameAttribute<_Ty>::clearMin()
{
	_min.enabled = false;
}

template<class _Ty>
inline bool GameAttribute<_Ty>::operator==(const GameAttribute& that) const
{
	return _value == that._value;
}

template<class _Ty>
inline bool GameAttribute<_Ty>::operator!=(const GameAttribute& that) const
{
	return !(*this == that);
}

template<class _Ty>
inline _Ty GameAttribute<_Ty>::adjust(_Ty value) const
{
	if (_min.enabled && value < _min.value) return _min.value;
	else if (_max.enabled && _max.value < value) return _max.value;
	else return value;
}

template<class _Ty>
inline void GameAttribute<_Ty>::adjustValue()
{
	_value = adjust(_value);
}
