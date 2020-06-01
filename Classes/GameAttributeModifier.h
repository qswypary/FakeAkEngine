/****************************************************************************
 GameAttributeModifier (header)

 @author qswypary

 ��ʾ�����Խ��е��޸ĵ��ࡣ
 ����4�ֻ������޸ķ�����
 ****************************************************************************/
#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include "json/document.h"
#include "GameAttribute.h"

class GameAttributeModifier {
public:
    // ��ʾ�޸ķ�����ö��
    enum ModifyingMethod {
        ADDITION,           // ֱ�Ӽ���
        SCALER,             // ֱ�ӳ���
        FINAL_ADDITION,     // ���ռ���
        FINAL_SCALER        // ���ճ���
    };

private:
    // �洢�޸ķ���ö�ٺ��ַ������ƶ�Ӧ��ϵ�� map
    static const std::map<std::string, ModifyingMethod> _MM_NAMES_MAP;

    std::string _attr_name;         // ���޸ĵ���������
    ModifyingMethod _method;        // �޸ķ���
    double _value;                  // �޸���ֵ

public:
    // ���ܱ��޸ĵ��������ơ���������ֵ�Ĺ��캯��
    GameAttributeModifier(std::string name, ModifyingMethod method, double value);

    // ���� Json �е� Object ����Ϊ�������ݵĹ��캯��
    GameAttributeModifier(const rapidjson::Value &object);

    // ��ȡ��������
    std::string getAttrName() const;

    // ��ȡ�޸ķ���
    ModifyingMethod getMethod() const;

    // ��ȡ�޸���ֵ
    double getValue() const;

private:
    // �����޸ķ��������޸���ֵ
    void adjustValue();
};