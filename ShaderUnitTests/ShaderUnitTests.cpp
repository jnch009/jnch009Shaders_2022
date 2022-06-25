#include "pch.h"
#include "CppUnitTest.h"
#include "../../jnch009Shaders_2022/src/utility/utilities.h";
#include "../../jnch009Shaders_2022/src/utility/utilities.cpp";
#include "../../../of_v0.10.0_vs2017_release/libs/glm/include/glm/vec4.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShaderUnitTests
{
	TEST_CLASS(ShaderUnitTests)
	{
	public:

		TEST_METHOD(determineColor_KEYPRESS_NOT_FOUND)
		{
			glm::vec4 actual = utilities::determineColor(123);
			Assert::AreEqual(actual.r, 1.0f);
			Assert::AreEqual(actual.g, 0.0f);
			Assert::AreEqual(actual.b, 0.0f);
			Assert::AreEqual(actual.w, 1.0f);
		}

		TEST_METHOD(determineColor_KEYPRESS_UP)
		{
			glm::vec4 actual = utilities::determineColor(57357);
			Assert::AreEqual(actual.r, 1.0f);
			Assert::AreEqual(actual.g, 1.0f);
			Assert::AreEqual(actual.b, 1.0f);
			Assert::AreEqual(actual.w, 0.25f);
		}
	};
}
