/****************************************************************************
 GameAttributeModifier

 @author qswypary

 表示对属性进行的修改的类。
 具有4种基本的修改方法。
 ****************************************************************************/
#include <vector>
#include "GameAttributeModifier.h"

const std::map<std::string, GameAttributeModifier::ModifyingMethod>
GameAttributeModifier::_MM_NAMES_MAP{
	{"ADDITION", ADDITION},
	{"SCALER", SCALER},
	{"FINAL_ADDITION", FINAL_ADDITION},
	{"FINAL_SCALER", FINAL_SCALER}
};

GameAttributeModifier::GameAttributeModifier(std::string name, ModifyingMethod method, double value) :
	_attr_name(name), _method(method), _value(value)
{
	adjustValue();
}

GameAttributeModifier::GameAttributeModifier(const rapidjson::Value &object)
{
	if (!object.IsObject()) {
		throw std::invalid_argument("the given value is not an object");
	}
	std::vector<std::string> keys = {
		std::string("attrName"), 
		std::string("modifyingMethod"), 
		std::string("value")
	};
	for (const auto& item : keys) {
		if (!object.HasMember(item.c_str())) {
			throw std::invalid_argument("the given object misses member \'" + item + "\'");
		}
	}

	const auto& anquote = object.GetObject()[keys[0].c_str()];
	if (anquote.IsString()) {
		_attr_name = anquote.GetString();
	}
	else {
		throw std::invalid_argument("the given object's member \'" + keys[0] + "\' has invalid type (should be string)");
	}

	const auto& mquote = object.GetObject()[keys[1].c_str()];
	if (mquote.IsString()) {
		if (_MM_NAMES_MAP.find(mquote.GetString()) == _MM_NAMES_MAP.end()) {
			throw std::invalid_argument("the given object's member \'" + keys[1] + "\' has invalid value");
		}
		_method = _MM_NAMES_MAP.at(mquote.GetString());
	}
	else {
		throw std::invalid_argument("the given object's member \'" + keys[1] + "\' has invalid type (should be string)");
	}

	const auto& vquote = object.GetObject()[keys[2].c_str()];
	if (vquote.IsDouble()) {
		_value = vquote.GetDouble();
	}
	else {
		throw std::invalid_argument("the given object's member \'" + keys[2] + "\' has invalid type (should be double)");
	}

	adjustValue();
}

std::string GameAttributeModifier::getAttrName() const
{
	return _attr_name;
}

GameAttributeModifier::ModifyingMethod GameAttributeModifier::getMethod() const
{
	return _method;
}

double GameAttributeModifier::getValue() const
{
	return _value;
}

void GameAttributeModifier::adjustValue()
{
	if (_value < 0) {
		if (_method == SCALER) {
			_value = 0;
		}
		else if (_method == FINAL_SCALER) {
			_value += 1;
			if (_value < 0) {
				_value = 0;
			}
		}
	}
}

