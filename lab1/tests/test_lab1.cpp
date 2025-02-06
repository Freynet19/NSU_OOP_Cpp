#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <iostream>
#include "FibonacciCached.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include "ValueNotFound.h"

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
    EXPECT_THROW(cache[4], ValueNotFound);
    cache.put(4, 40);
    EXPECT_THROW(cache[1], ValueNotFound);
    cache.put(3, 30);
    EXPECT_EQ(cache[3], 30);
    EXPECT_EQ(cache[4], 40);
    cache.put(1, 10);
    EXPECT_THROW(cache[2], ValueNotFound);
}

TEST(RawCacheTests, SimpleLFUTest) {
    LFUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    EXPECT_THROW(cache[4], ValueNotFound);
    EXPECT_EQ(cache[3], 30);
    EXPECT_EQ(cache[3], 30);
    cache.put(4, 40);
    EXPECT_EQ(cache[4], 40);
    EXPECT_THROW(cache[1], ValueNotFound);
    EXPECT_EQ(cache[2], 20);
    cache.put(1, 10);
    EXPECT_THROW(cache[2], ValueNotFound);
}

TEST(FibCachedTests, SimpleTest) {
    std::stringstream stdoutBuf;
    std::streambuf* oldBuffer = std::cout.rdbuf(stdoutBuf.rdbuf());

    FibonacciCached fc(2, СacheType::LRU);
    fc.getAndPrintFib(20);
    EXPECT_EQ("Calculated value:\t  6765", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(5);
    EXPECT_EQ("Calculated value:\t  5", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(20);
    EXPECT_EQ("Value found in cache: 6765", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(4);
    EXPECT_EQ("Calculated value:\t  3", findLastLine(stdoutBuf.str()));
    fc.getAndPrintFib(5);
    EXPECT_EQ("Calculated value:\t  5", findLastLine(stdoutBuf.str()));

    std::cout.rdbuf(oldBuffer);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
