/****************************************************************************
 GameMutableAttribute

 @author qswypary

 可变属性的类，继承自 GameDoubleAttribute。
 内含了与该属性对应的 GameAttributeModifier 对象。
 ****************************************************************************/
#include <algorithm>
#include "GameAttributeModifier.h"
#include "GameMutableAttribute.h"

GameMutableAttribute::GameMutableAttribute(const std::string& name, const double& value):
	GameDoubleAttribute(name, value)
{
	_final_value = value;
}

double GameMutableAttribute::getValue() const
{
	return _final_value;
}

std::list<GameAttributeModifier> GameMutableAttribute::getModifiers() const
{
	return _modifiers;
}

void GameMutableAttribute::addModifier(const GameAttributeModifier& mod)
{
	if (mod.getAttrName() != getName()) {
		throw std::invalid_argument("modifier's attribute name is different from attribute's");
	}
	GameAttributeModifier::ModifyingMethod method = mod.getMethod();
	auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
		[method](const auto& item) { return item.getMethod() >= method; });
	_modifiers.insert(it, mod);
	refresh();
}

void GameMutableAttribute::addModifiers(std::list<GameAttributeModifier> modlist)
{
	modlist.sort([](auto a, auto b) { return a.getMethod() < b.getMethod(); });
	auto it = _modifiers.begin();
	for (const auto& item : modlist) {
		if (item.getAttrName() != getName()) {
			throw std::invalid_argument("modifier's attribute name is different from attribute's");
		}
		GameAttributeModifier::ModifyingMethod method = item.getMethod();
		it = std::find_if(it, _modifiers.end(),
			[method](const auto& item) { return item.getMethod() >= method; });
		_modifiers.insert(it, item);
	}
	refresh();
}

void GameMutableAttribute::deleteModifiers()
{
	_modifiers = std::list<GameAttributeModifier>();
	refresh();
}

void GameMutableAttribute::refresh()
{
	refreshValue();
}

void GameMutableAttribute::refreshValue()
{
	double addition = 0.0, scaler = 0.0, 
		faddition = 0.0, fscaler = 1.0;
	for (auto item : _modifiers) {
		double value = item.getValue();
		switch (item.getMethod())
		{
		case GameAttributeModifier::ADDITION:
			addition += value;
			break;
		case GameAttributeModifier::SCALER:
			scaler += value;
			break;
		case GameAttributeModifier::FINAL_ADDITION:
			faddition += value;
			break;
		case GameAttributeModifier::FINAL_SCALER:
			fscaler *= value;
			break;
		default:
			break;
		}
	}
	_final_value = adjust(((GameDoubleAttribute::getValue() + addition) * (1 + scaler) + faddition) * fscaler);
}
