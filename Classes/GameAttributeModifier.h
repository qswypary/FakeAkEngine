/****************************************************************************
 GameAttributeModifier (header)

 @author qswypary

 表示对属性进行的修改的类。
 具有4种基本的修改方法。
 ****************************************************************************/
#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include "json/document.h"
#include "GameAttribute.h"

class GameAttributeModifier {
public:
    // 表示修改方法的枚举
    enum ModifyingMethod {
        ADDITION,           // 直接加算
        SCALER,             // 直接乘算
        FINAL_ADDITION,     // 最终加算
        FINAL_SCALER        // 最终乘算
    };

private:
    // 存储修改方法枚举和字符串名称对应关系的 map
    static const std::map<std::string, ModifyingMethod> _MM_NAMES_MAP;

    std::string _attr_name;         // 被修改的属性名称
    ModifyingMethod _method;        // 修改方法
    double _value;                  // 修改数值

public:
    // 接受被修改的属性名称、方法和数值的构造函数
    GameAttributeModifier(std::string name, ModifyingMethod method, double value);

    // 接受 Json 中的 Object 解析为对象内容的构造函数
    GameAttributeModifier(const rapidjson::Value &object);

    // 获取属性名称
    std::string getAttrName() const;

    // 获取修改方法
    ModifyingMethod getMethod() const;

    // 获取修改数值
    double getValue() const;

private:
    // 根据修改方法调整修改数值
    void adjustValue();
};