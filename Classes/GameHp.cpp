/****************************************************************************
 GameHp

 @author qswypary

 表示游戏中类似血量的，含有“上限”和“实际值”的属性。
 继承自 GameMutableAttribute。
 可以指定这类属性在百分比变动时的表现。
 ****************************************************************************/
#include "GameHp.h"

GameHp::GameHp(const std::string& name, const double& value) :
    GameMutableAttribute(name, value)
{
    _max_prev = _actual = value;
}

double GameHp::getActualValue() const
{
	return _actual;
}

GameHp::Behavior GameHp::getBehaviorWhenIncrease() const
{
	return _increase_behavior;
}

GameHp::Behavior GameHp::getBehaviorWhenDecrease() const
{
	return _decrease_behavior;
}

void GameHp::addActualValue(double value)
{
    _actual += value;
    adjustActualValue();
}

void GameHp::addActualValueByPercent(double percent)
{
    _actual += GameMutableAttribute::getValue() * percent;
    adjustActualValue();
}

void GameHp::setBehaviorWhenIncrease(Behavior bhv)
{
    _increase_behavior = bhv;
}

void GameHp::setBehaviorWhenDecrease(Behavior bhv)
{
    _decrease_behavior = bhv;
}

void GameHp::refresh()
{
    GameMutableAttribute::refresh();
    double now = GameMutableAttribute::getValue();
    Behavior bhv;
    if (now > _max_prev) bhv = _increase_behavior;
    else if (now < _max_prev) bhv = _decrease_behavior;
    else return;
    switch (bhv)
    {
    case GameHp::FIXED_ACTUAL_VALUE:
        break;
    case GameHp::FIXED_REDUCED_PART:
        _actual = now - (_max_prev - _actual);
        break;
    case GameHp::CHANGE_BY_RATIO:
        _actual = now * (_actual / _max_prev);
        break;
    default:
        break;
    }
    adjustActualValue();
    _max_prev = now;
}

void GameHp::adjustActualValue()
{
    double now = GameMutableAttribute::getValue();
    if (_actual > now) _actual = now;
    else if (_actual < 0.0) _actual = 0.0;
}
