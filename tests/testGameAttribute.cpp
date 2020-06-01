#include "pch.h"
#include "CppUnitTest.h"
#include "../Classes/GameAttribute.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGame
{
	TEST_CLASS(TestGameAttribute)
	{
	public:
		
		TEST_METHOD(TestInit)
		{
			GameAttribute<int>* ga1 = new GameAttribute<int>("ga1", 1);
			GameAttribute<double>* ga2 = new GameAttribute<double>("ga2", 1.0);
			GameAttribute<std::string>* ga3 = new GameAttribute<std::string>("ga3", "STUNNED");
			GameAttribute<bool>* ga4 = new GameAttribute<bool>("ga4", true);

			Assert::AreEqual(std::string("ga1"), ga1->getName());
			Assert::AreEqual(std::string("ga2"), ga2->getName());
			Assert::AreEqual(std::string("ga3"), ga3->getName());
			Assert::AreEqual(std::string("ga4"), ga4->getName());

			Assert::AreEqual(1, ga1->getValue());
			Assert::AreEqual(1.0, ga2->getValue());
			Assert::AreEqual(std::string("STUNNED"), ga3->getValue());
			Assert::AreEqual(true, ga4->getValue());

			delete ga1;
			delete ga2;
			delete ga3;
			delete ga4;
		}

		TEST_METHOD(TestMaxAndMin)
		{
			GameAttribute<double>* ga1 = new GameAttribute<double>("ga1", 1.0);
			double max = 20.0, min = 0.0;

			ga1->setMax(max);
			ga1->setMin(min);
			Assert::AreEqual(1.0, ga1->getValue(), 0.0001);
			Assert::IsTrue(ga1->isValid(10.0));
			Assert::IsTrue(ga1->isValid(min));
			Assert::IsTrue(ga1->isValid(max));
			Assert::IsFalse(ga1->isValid(-10.0));
			Assert::IsFalse(ga1->isValid(30.0));

			ga1->clearMax();
			Assert::AreEqual(1.0, ga1->getValue(), 0.0001);
			Assert::IsTrue(ga1->isValid(10.0));
			Assert::IsTrue(ga1->isValid(min));
			Assert::IsTrue(ga1->isValid(max));
			Assert::IsFalse(ga1->isValid(-10.0));
			Assert::IsTrue(ga1->isValid(30.0));

			ga1->clearMin();
			Assert::AreEqual(1.0, ga1->getValue(), 0.0001);
			Assert::IsTrue(ga1->isValid(10.0));
			Assert::IsTrue(ga1->isValid(min));
			Assert::IsTrue(ga1->isValid(max));
			Assert::IsTrue(ga1->isValid(-10.0));
			Assert::IsTrue(ga1->isValid(30.0));

			ga1->setMax(20.0);
			Assert::AreEqual(1.0, ga1->getValue(), 0.0001);
			Assert::IsTrue(ga1->isValid(10.0));
			Assert::IsTrue(ga1->isValid(min));
			Assert::IsTrue(ga1->isValid(max));
			Assert::IsTrue(ga1->isValid(-10.0));
			Assert::IsFalse(ga1->isValid(30.0));

			ga1->setMin(10.0);
			Assert::AreEqual(10.0, ga1->getValue(), 0.0001);
			Assert::ExpectException<std::invalid_argument>([ga1]() { ga1->setMax(5.0); });
			Assert::ExpectException<std::invalid_argument>([ga1]() { ga1->setMin(30.0); });

			delete ga1;
		}

		TEST_METHOD(TestOperator)
		{
			GameAttribute<std::string>* ga1 = new GameAttribute<std::string>("ga1", "STUNNED");
			GameAttribute<std::string>* ga2 = new GameAttribute<std::string>("ga2", "STUNNED");
			GameAttribute<std::string>* ga3 = new GameAttribute<std::string>("ga3", "FROZEN");

			Assert::IsTrue(*ga1 == *ga2);
			Assert::IsTrue(*ga1 != *ga3);

			delete ga1;
			delete ga2;
			delete ga3;
		}

		TEST_METHOD(TestAdjust)
		{
			GameAttribute<double>* ga1 = new GameAttribute<double>("ga1", 10.0);
			Assert::AreEqual(10.0, ga1->getValue());

			ga1->setMax(5.0);
			Assert::AreEqual(5.0, ga1->getValue());

			ga1->clearMax();
			ga1->setMin(8.0);
			Assert::AreEqual(8.0, ga1->getValue());

			ga1->clearMin();
			Assert::AreEqual(8.0, ga1->getValue());

			delete ga1;
		}
	};
}
