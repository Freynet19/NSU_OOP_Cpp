#include <gtest/gtest.h>
#include <sstream>
#include "FibonacciCached.h"
#include "LRUCache.h"
#include "LFUCache.h"

std::string findLastLine(const std::string& stdoutStr) {
    size_t lastNewlinePos = stdoutStr.rfind('\n',
        stdoutStr.find_last_of('\n') - 1);
    std::string lastLine = stdoutStr.substr(lastNewlinePos + 1,
        stdoutStr.find_last_of('\n') - lastNewlinePos - 1);
    return lastLine;
}

TEST(RawCacheTests, SimpleLRUTest) {
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    EXPECT_EQ(cache[2], 20);
    EXPECT_EQ(cache[4], 0);
    cache.put(4, 40);
    EXPECT_EQ(cache[1], 0);
    cache.put(3, 33);
    EXPECT_EQ(cache[3], 33);
    EXPECT_EQ(cache[4], 40);
    cache.put(1, 10);
    EXPECT_EQ(cache[2], 0);
}

TEST(RawCacheTests, SimpleLFUTest) {
    LFUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    EXPECT_EQ(cache[4], 0);
    EXPECT_EQ(cache[3], 30);
    EXPECT_EQ(cache[3], 30);
    cache.put(4, 40);
    EXPECT_EQ(cache[4], 40);
    EXPECT_EQ(cache[1], 0);
    EXPECT_EQ(cache[2], 20);
    cache.put(1, 10);
    EXPECT_EQ(cache[2], 0);
}

TEST(FibCachedTests, SimpleTest) {
    std::stringstream stdoutBuf;
    std::streambuf* oldBuffer = std::cout.rdbuf(stdoutBuf.rdbuf());

    FibonacciCached fc(2, 1);
    fc.getAndPrintFib(20);
    EXPECT_EQ("Calculated value: \t6765", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(5);
    EXPECT_EQ("Calculated value: \t5", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(20);
    EXPECT_EQ("Value found in cache:\t6765", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(4);
    EXPECT_EQ("Calculated value: \t3", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(5);
    EXPECT_EQ("Calculated value: \t5", findLastLine(stdoutBuf.str()));

    std::cout.rdbuf(oldBuffer);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
