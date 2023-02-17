#include "CppUnitTest.h"
#include <glm/vec4.hpp>
#include "Utility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShaderUnitTests
{
	TEST_CLASS(ShaderUnitTests)
	{
	public:
		TEST_METHOD(determineColor_KEYPRESS_NOT_FOUND)
		{
			glm::vec4 actual = Utility::determineColor(123);
			Assert::AreEqual(actual.r, 1.0f);
			Assert::AreEqual(actual.g, 0.0f);
			Assert::AreEqual(actual.b, 0.0f);
			Assert::AreEqual(actual.w, 1.0f);
		}

		TEST_METHOD(determineColor_KEYPRESS_UP)
		{
			glm::vec4 actual = Utility::determineColor(57357);
			Assert::AreEqual(actual.r, 1.0f);
			Assert::AreEqual(actual.g, 1.0f);
			Assert::AreEqual(actual.b, 1.0f);
			Assert::AreEqual(actual.w, 0.25f);
		}
	};
}
