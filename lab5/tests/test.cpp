#include "../include/memory.h"
#include "../include/vector.h"
#include <gtest/gtest.h>
#include <string>

// Определение ComplexType
struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, std::string name) : id(id), name(std::move(name)) {}
};

// Тесты MemoryResource
TEST(MemoryResourceTests, AllocationDeallocation) {
    TestMemoryResource memory_resource;

    void* ptr1 = memory_resource.do_allocate(16, alignof(int));
    void* ptr2 = memory_resource.do_allocate(32, alignof(double));

    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);

    memory_resource.do_deallocate(ptr1, 16, alignof(int));
    memory_resource.do_deallocate(ptr2, 32, alignof(double));
}

// Тесты Vector с простыми типами
TEST(VectorTests, PushBackAndAccess) {
    MemoryResource memory_resource;
    Vector<int> vector(&memory_resource);

    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    ASSERT_EQ(vector.size(), 3);
    EXPECT_EQ(vector[0], 10);
    EXPECT_EQ(vector[1], 20);
    EXPECT_EQ(vector[2], 30);
}

// Тесты Vector с ComplexType
TEST(VectorTests, ComplexTypeOperations) {
    MemoryResource memory_resource;
    Vector<ComplexType> vector(&memory_resource);

    vector.push_back(ComplexType(1, "Alice"));
    vector.push_back(ComplexType(2, "Bob"));

    ASSERT_EQ(vector.size(), 2);
    EXPECT_EQ(vector[0].id, 1);
    EXPECT_EQ(vector[0].name, "Alice");
    EXPECT_EQ(vector[1].id, 2);
    EXPECT_EQ(vector[1].name, "Bob");
}