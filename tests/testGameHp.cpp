#include "pch.h"
#include "CppUnitTest.h"
#include "../Classes/GameHp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGame
{
	TEST_CLASS(TestGameHp)
	{
	public:

		TEST_METHOD(TestInit)
		{
			GameHp* gh1 = new GameHp("gh1", 1.0);

			Assert::AreEqual(1.0, gh1->getActualValue(), 0.0001);

			delete gh1;
		}

		TEST_METHOD(TestAdd)
		{
			GameHp* gh1 = new GameHp("gh1", 3000.0);

			gh1->addActualValue(-100.0);
			Assert::AreEqual(2900.0, gh1->getActualValue(), 0.0001);
			gh1->addActualValue(200.0);
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);
			gh1->addActualValueByPercent(-0.05);
			Assert::AreEqual(2850.0, gh1->getActualValue(), 0.0001);
			gh1->addActualValueByPercent(0.10);
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);
			gh1->addActualValueByPercent(-2.0);
			Assert::AreEqual(0.0, gh1->getActualValue(), 0.0001);

			delete gh1;
		}

		TEST_METHOD(TestModifiers)
		{
			GameHp* gh1 = new GameHp("gh1", 3000.0);

			GameAttributeModifier* gam1 = new GameAttributeModifier("gh1", GameAttributeModifier::ADDITION, -1000.0);
			GameAttributeModifier* gam2 = new GameAttributeModifier("gh1", GameAttributeModifier::FINAL_SCALER, 2.0);
			GameAttributeModifier* gam3 = new GameAttributeModifier("gh1", GameAttributeModifier::FINAL_SCALER, 0.5);

			gh1->addModifier(*gam1);
			Assert::AreEqual(2000.0, gh1->getActualValue(), 0.0001);
			gh1->addModifier(*gam2);
			Assert::AreEqual(4000.0, gh1->getActualValue(), 0.0001);
			gh1->addModifier(*gam3);
			Assert::AreEqual(2000.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();

			gh1->setBehaviorWhenIncrease(GameHp::FIXED_ACTUAL_VALUE);
			gh1->setBehaviorWhenDecrease(GameHp::FIXED_ACTUAL_VALUE);
			gh1->addModifier(*gam2);
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);
			gh1->addModifier(*gam3);
			Assert::AreEqual(1500.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();
			Assert::AreEqual(1500.0, gh1->getActualValue(), 0.0001);

			gh1->setBehaviorWhenIncrease(GameHp::FIXED_REDUCED_PART);
			gh1->setBehaviorWhenDecrease(GameHp::FIXED_REDUCED_PART);
			gh1->addModifier(*gam2);
			Assert::AreEqual(4500.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();
			Assert::AreEqual(1500.0, gh1->getActualValue(), 0.0001);
			gh1->addModifier(*gam3);
			Assert::AreEqual(0.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();
			Assert::AreEqual(1500.0, gh1->getActualValue(), 0.0001);

			gh1->setBehaviorWhenIncrease(GameHp::CHANGE_BY_RATIO);
			gh1->setBehaviorWhenDecrease(GameHp::FIXED_ACTUAL_VALUE);
			gh1->addModifier(*gam2);
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);
			gh1->addModifier(*gam3);
			Assert::AreEqual(1500.0, gh1->getActualValue(), 0.0001);
			gh1->deleteModifiers();
			Assert::AreEqual(3000.0, gh1->getActualValue(), 0.0001);

			delete gh1;
			delete gam1;
			delete gam2;
			delete gam3;
		}
	};
}
