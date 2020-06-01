/****************************************************************************
 GameBuff (header)

 @author qswypary

 表示游戏中增益或减益效果的类。
 分为改变属性值，以及特殊异常效果两类进行处理。
 ****************************************************************************/
#pragma once
#include <list>
#include <string>

class GameBuff {
private:
    std::string _buff_key;      // 对象的名称
};