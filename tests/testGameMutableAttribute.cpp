#include "pch.h"
#include "CppUnitTest.h"
#include "../Classes/GameMutableAttribute.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGame
{
	TEST_CLASS(TestGameMutableAttribute)
	{
	public:

		TEST_METHOD(TestInit)
		{
			GameMutableAttribute* gma1 = new GameMutableAttribute("gma1", 1.0);

			Assert::AreEqual(std::string("gma1"), gma1->getName());
			Assert::AreEqual(1.0, gma1->getValue());

			delete gma1;
		}

		TEST_METHOD(TestModifiers)
		{
			GameMutableAttribute* gma1 = new GameMutableAttribute("gma1", 30.0);
			gma1->setMax(100.0);
			gma1->setMin(10.0);

			GameAttributeModifier* gam1 = new GameAttributeModifier("gma1", GameAttributeModifier::ADDITION, 2.0);
			GameAttributeModifier* gam2 = new GameAttributeModifier("gma1", GameAttributeModifier::SCALER, 0.5);
			GameAttributeModifier* gam3 = new GameAttributeModifier("gma1", GameAttributeModifier::FINAL_ADDITION, 2.0);
			GameAttributeModifier* gam4 = new GameAttributeModifier("gma1", GameAttributeModifier::FINAL_SCALER, 0.5);

			gma1->addModifier(*gam1);
			Assert::AreEqual(32.0, gma1->getValue());
			gma1->addModifier(*gam2);
			Assert::AreEqual(48.0, gma1->getValue());
			gma1->addModifier(*gam3);
			Assert::AreEqual(50.0, gma1->getValue());
			gma1->addModifier(*gam4);
			Assert::AreEqual(25.0, gma1->getValue());

			gma1->addModifier(*gam1);
			Assert::AreEqual(26.5, gma1->getValue());
			gma1->addModifier(*gam2);
			Assert::AreEqual(35.0, gma1->getValue());
			gma1->addModifier(*gam3);
			Assert::AreEqual(36.0, gma1->getValue());
			gma1->addModifier(*gam4);
			Assert::AreEqual(18.0, gma1->getValue());

			gma1->deleteModifiers();
			Assert::AreEqual(30.0, gma1->getValue());

			std::list<GameAttributeModifier> ls1 = {
				GameAttributeModifier("gma1", GameAttributeModifier::ADDITION, 20.0),
				GameAttributeModifier("gma1", GameAttributeModifier::SCALER, 2.0)
			};
			std::list<GameAttributeModifier> ls2 = {
				GameAttributeModifier("gma1", GameAttributeModifier::FINAL_ADDITION, -200.0),
				GameAttributeModifier("gma1", GameAttributeModifier::FINAL_SCALER, 3.0)
			};

			gma1->addModifiers(ls1);
			Assert::AreEqual(100.0, gma1->getValue());
			gma1->addModifiers(ls2);
			Assert::AreEqual(10.0, gma1->getValue());

			std::list<GameAttributeModifier> ls3 = {
				GameAttributeModifier("gma1", GameAttributeModifier::ADDITION, 20.0),
				GameAttributeModifier("gma1", GameAttributeModifier::SCALER, 2.0),
				GameAttributeModifier("gma1", GameAttributeModifier::FINAL_ADDITION, -200.0),
				GameAttributeModifier("gma1", GameAttributeModifier::FINAL_SCALER, 3.0)
			};
			std::list<GameAttributeModifier> ls4 = gma1->getModifiers();

			for (auto it3 = ls3.begin(), it4 = ls4.begin();
				it3 != ls3.end() && it4 != ls4.end();
				++it3, ++it4) {
				Assert::AreEqual(it3->getAttrName(), it4->getAttrName());
				Assert::AreEqual(it3->getValue(), it4->getValue());
			}

			gma1->deleteModifiers();

			GameAttributeModifier* gam5 = new GameAttributeModifier("gma2", GameAttributeModifier::ADDITION, 2.0);
			Assert::ExpectException<std::invalid_argument>([gma1, gam5]() { gma1->addModifier(*gam5); });

			delete gma1;
			delete gam1;
			delete gam2;
			delete gam3;
			delete gam4;
			delete gam5;
		}
	};
}
