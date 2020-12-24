#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.2(b).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest112b
{
	TEST_CLASS(UnitTest112b)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char f[6] = "f.dat";
			int t = goodMathPhys(f);
			Assert::AreEqual(t, 0);
		}
	};
}
