/****************************************************************************
 GameAttribute (header)

 @author qswypary

 ��ʾ��Ϸ�е�λ�ĵ������Ե���ģ�塣
 ****************************************************************************/
#pragma once
#include <string>
#include <stdexcept>

template <class _Ty>
class GameAttribute {
private:
	// ��ʾ��ֵ��С�������ƵĽṹ��
	struct Bound {
		bool enabled;           // �����Ƿ�������
		_Ty value;              // ���Ƶ�ֵ
	};

	const std::string _name;    // ��������
	_Ty _value;                 // ����ֵ
	Bound _max = {};            // ����ֵ����
	Bound _min = {};            // ����ֵ����

public:
	// �����������ƺ�ֵ�Ĺ��캯��
	GameAttribute(const std::string& name, const _Ty& value);

	// ��ȡ��������
	std::string getName() const;

	// ��ȡ����ֵ
	virtual _Ty getValue() const;

	// ������ֵ�Ƿ����������Ҫ��
	bool isValid(const _Ty& value) const;

	// ��������
	// �����׳����� std::invalid_argument
	void setMax(const _Ty& max);

	// �������
	void clearMax();

	// ��������
	// �����׳����� std::invalid_argument
	void setMin(const _Ty& min);

	// �������
	void clearMin();

	// ��������أ���ֵ�Ƚ�
	bool operator==(const GameAttribute& that) const;
	bool operator!=(const GameAttribute& that) const;

protected:
	// ��������ֵ
	_Ty adjust(_Ty value) const;

private:
	// ����������Χ������ֵ
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
