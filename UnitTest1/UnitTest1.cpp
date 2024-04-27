#include "pch.h"
#include "CppUnitTest.h"
#include "../An In-place Multidimensional/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestCreateArrayAtMemorySingle)
        {
            void* memory = nullptr;
            size_t size = CreateArrayAtMemory<int>(memory, 5);
            Assert::AreEqual(size, sizeof(int) * 5);
        }
        TEST_METHOD(TestCreateArrayAtMemoryNested)
        {
            void* memory = nullptr;
            size_t size = CreateArrayAtMemory<int>(memory, 2, 3);
            Assert::AreEqual(size, (size_t)40);
            free(memory);
        }
        TEST_METHOD(TestMemoryManager)
        {
            MemoryManager memoryManager(sizeof(int) * 10);
            void* memory = memoryManager.getMemory();
            Assert::IsNotNull(memory);

            std::vector<char> a1(CreateArrayAtMemory(memory, 5));
            Assert::AreEqual(a1.size(), (size_t)5);


            memory = memoryManager.getMemory(); 
            Assert::IsNotNull(memory); 
        }

	};
}

