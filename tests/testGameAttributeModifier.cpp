/****************************************************************************
 GameAttributeModifier

 @author qswypary

 表示对属性进行的修改的类。
 具有4种基本的修改方法。
 ****************************************************************************/
#include "pch.h"
#include "CppUnitTest.h"
#include "../Classes/GameAttributeModifier.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGame
{
	TEST_CLASS(TestGameAttributeModifier)
	{
	public:

		TEST_METHOD(TestInit)
		{
			std::string str1
				= "{ \"attrName\" : \"ga1\", \"modifyingMethod\" : \"SCALER\", \"value\" : 2.0 }";
			std::string str2
				= "[ \"im\", \"a\", \"json\", \"value\" ]";
			std::string str3
				= "{ \"attrName\" : \"ga1\", \"modifyingMethod\" : \"SCALER\", \"sthwrong\" : 2.0 }";
			std::string str4
				= "{ \"attrName\" : \"ga1\", \"modifyingMethod\" : \"SCALER\", \"value\" : \"sthwrong\" }";

			rapidjson::Document d;
			d.Parse(str1.c_str());

			GameAttributeModifier* gam1
				= new GameAttributeModifier("ga1", GameAttributeModifier::ADDITION, 1.0);
			GameAttributeModifier* gam2
				= new GameAttributeModifier(d);

			Assert::AreEqual(std::string("ga1"), gam1->getAttrName());
			Assert::AreEqual(1.0, gam1->getValue());
			Assert::AreEqual(std::string("ga1"), gam2->getAttrName());
			Assert::AreEqual(2.0, gam2->getValue());

			d.Parse(str2.c_str());
			Assert::ExpectException<std::invalid_argument>([&d]() { GameAttributeModifier tmp(d); });
			d.Parse(str3.c_str());
			Assert::ExpectException<std::invalid_argument>([&d]() { GameAttributeModifier tmp(d); });
			d.Parse(str4.c_str());
			Assert::ExpectException<std::invalid_argument>([&d]() { GameAttributeModifier tmp(d); });

			delete gam1;
			delete gam2;
		}

		TEST_METHOD(TestAdjust) {
			GameAttributeModifier* gam1
				= new GameAttributeModifier("ga1", GameAttributeModifier::SCALER, -1.0);
			GameAttributeModifier* gam2
				= new GameAttributeModifier("ga1", GameAttributeModifier::FINAL_SCALER, -0.7);
			GameAttributeModifier* gam3
				= new GameAttributeModifier("ga1", GameAttributeModifier::FINAL_SCALER, -2.0);

			Assert::AreEqual(0.0, gam1->getValue());
			Assert::AreEqual(0.3, gam2->getValue(), 0.0001);
			Assert::AreEqual(0.0, gam3->getValue());
		}
	};
}
