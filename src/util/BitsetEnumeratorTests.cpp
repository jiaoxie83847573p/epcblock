// Copyright 2016 epc Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "lib/catch.hpp"
#include "util/BitsetEnumerator.h"
#include "util/Logging.h"
#include <ostream>

using namespace epc;

static void
expect_bitsets(BitsetEnumerator& be, std::vector<std::bitset<64>> const& expect)
{
    std::vector<std::bitset<64>> tmp;
    while (be)
    {
        tmp.emplace_back(*be);
        ++be;
    }
    REQUIRE(expect.size() == tmp.size());
    bool same = true;
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if (expect[i] != tmp[i])
        {
            same = false;
            std::cerr << "Bitsets differ at entry " << i << std::endl;
            std::cerr << "expected " << expect[i] << std::endl;
            std::cerr << "     got " << tmp[i] << std::endl;
            break;
        }
    }
    if (!same)
    {
        std::cerr << "Bitsets differ" << std::endl;
        ;
        std::cerr << "     got: " << std::endl;
        for (auto const& b : tmp)
        {
            std::cerr << "         " << b << std::endl;
        }
        std::cerr << "expected: " << std::endl;
        for (auto const& b : expect)
        {
            std::cerr << "         " << b << std::endl;
        }
    }
    REQUIRE(same);
}

TEST_CASE("ConstantEnumerator", "[bitset]")
{
    ConstantEnumerator ce(std::bitset<64>(0xff));
    expect_bitsets(ce, {0xff});
}

TEST_CASE("PermutationEnumerator", "[bitset]")
{
    PermutationEnumerator pe(4, 6);
    expect_bitsets(
        pe,
        {
            0b0000000000000000000000000000000000000000000000000000000000001111ULL,
            0b0000000000000000000000000000000000000000000000000000000000010111ULL,
            0b0000000000000000000000000000000000000000000000000000000000011011ULL,
            0b0000000000000000000000000000000000000000000000000000000000011101ULL,
            0b0000000000000000000000000000000000000000000000000000000000011110ULL,
            0b0000000000000000000000000000000000000000000000000000000000100111ULL,
            0b0000000000000000000000000000000000000000000000000000000000101011ULL,
            0b0000000000000000000000000000000000000000000000000000000000101101ULL,
            0b0000000000000000000000000000000000000000000000000000000000101110ULL,
            0b0000000000000000000000000000000000000000000000000000000000110011ULL,
            0b0000000000000000000000000000000000000000000000000000000000110101ULL,
            0b0000000000000000000000000000000000000000000000000000000000110110ULL,
            0b0000000000000000000000000000000000000000000000000000000000111001ULL,
            0b0000000000000000000000000000000000000000000000000000000000111010ULL,
            0b0000000000000000000000000000000000000000000000000000000000111100ULL,
        });
}

TEST_CASE("CartesianProductEnumerator-of-constants", "[bitset]")
{
    CartesianProductEnumerator cpe(
        {std::make_shared<ConstantEnumerator>(std::bitset<64>(0x0000ff)),
         std::make_shared<ConstantEnumerator>(std::bitset<64>(0xff0000))});
    expect_bitsets(cpe, {0xff00ff});
}

TEST_CASE("SelectionEnumerator-of-constants", "[bitset]")
{
    SelectionEnumerator spe(
        std::make_shared<PermutationEnumerator>(2, 3),
        {
            std::make_shared<ConstantEnumerator>(std::bitset<64>(0xff0000)),
            std::make_shared<ConstantEnumerator>(std::bitset<64>(0x00ff00)),
            std::make_shared<ConstantEnumerator>(std::bitset<64>(0x0000ff)),
        });
    expect_bitsets(
        spe,
        {0b0000000000000000000000000000000000000000111111111111111100000000ULL,
         0b0000000000000000000000000000000000000000111111110000000011111111ULL,
         0b0000000000000000000000000000000000000000000000001111111111111111ULL});
}

TEST_CASE("SelectionEnumerator-of-bit-numbers", "[bitset]")
{
    auto se = SelectionEnumerator::bitNumbers(4, {1, 2, 7, 8, 30, 31});
    expect_bitsets(
        *se,
        {0b0000000000000000000000000000000000000000000000000000000110000110ULL,
         0b0000000000000000000000000000000001000000000000000000000010000110ULL,
         0b0000000000000000000000000000000001000000000000000000000100000110ULL,
         0b0000000000000000000000000000000001000000000000000000000110000010ULL,
         0b0000000000000000000000000000000001000000000000000000000110000100ULL,
         0b0000000000000000000000000000000010000000000000000000000010000110ULL,
         0b0000000000000000000000000000000010000000000000000000000100000110ULL,
         0b0000000000000000000000000000000010000000000000000000000110000010ULL,
         0b0000000000000000000000000000000010000000000000000000000110000100ULL,
         0b0000000000000000000000000000000011000000000000000000000000000110ULL,
         0b0000000000000000000000000000000011000000000000000000000010000010ULL,
         0b0000000000000000000000000000000011000000000000000000000010000100ULL,
         0b0000000000000000000000000000000011000000000000000000000100000010ULL,
         0b0000000000000000000000000000000011000000000000000000000100000100ULL,
         0b0000000000000000000000000000000011000000000000000000000110000000ULL});
}

TEST_CASE("CartesianProductEnumerator-of-selections", "[bitset]")
{
    CartesianProductEnumerator cpe(
        {SelectionEnumerator::bitNumbers(2, std::vector<size_t>({0, 1, 2})),
         SelectionEnumerator::bitNumbers(
             5, std::vector<size_t>({6, 7, 8, 32, 35, 54}))});
    expect_bitsets(
        cpe,
        {0b0000000000000000000000000000100100000000000000000000000111000011ULL,
         0b0000000000000000000000000000100100000000000000000000000111000101ULL,
         0b0000000000000000000000000000100100000000000000000000000111000110ULL,
         0b0000000001000000000000000000000100000000000000000000000111000011ULL,
         0b0000000001000000000000000000000100000000000000000000000111000101ULL,
         0b0000000001000000000000000000000100000000000000000000000111000110ULL,
         0b0000000001000000000000000000100000000000000000000000000111000011ULL,
         0b0000000001000000000000000000100000000000000000000000000111000101ULL,
         0b0000000001000000000000000000100000000000000000000000000111000110ULL,
         0b0000000001000000000000000000100100000000000000000000000011000011ULL,
         0b0000000001000000000000000000100100000000000000000000000011000101ULL,
         0b0000000001000000000000000000100100000000000000000000000011000110ULL,
         0b0000000001000000000000000000100100000000000000000000000101000011ULL,
         0b0000000001000000000000000000100100000000000000000000000101000101ULL,
         0b0000000001000000000000000000100100000000000000000000000101000110ULL,
         0b0000000001000000000000000000100100000000000000000000000110000011ULL,
         0b0000000001000000000000000000100100000000000000000000000110000101ULL,
         0b0000000001000000000000000000100100000000000000000000000110000110ULL});
}

TEST_CASE("CartesianProductEnumerator-of-mixture", "[bitset]")
{
    CartesianProductEnumerator cpe(
        {SelectionEnumerator::bitNumbers(2, std::vector<size_t>({0, 1, 2})),
         std::make_shared<ConstantEnumerator>(std::bitset<64>(0x00ff00)),
         SelectionEnumerator::bitNumbers(
             5, std::vector<size_t>({6, 7, 8, 32, 35, 54}))});
    expect_bitsets(
        cpe,
        {0b0000000000000000000000000000100100000000000000001111111111000011ULL,
         0b0000000000000000000000000000100100000000000000001111111111000101ULL,
         0b0000000000000000000000000000100100000000000000001111111111000110ULL,
         0b0000000001000000000000000000000100000000000000001111111111000011ULL,
         0b0000000001000000000000000000000100000000000000001111111111000101ULL,
         0b0000000001000000000000000000000100000000000000001111111111000110ULL,
         0b0000000001000000000000000000100000000000000000001111111111000011ULL,
         0b0000000001000000000000000000100000000000000000001111111111000101ULL,
         0b0000000001000000000000000000100000000000000000001111111111000110ULL,
         0b0000000001000000000000000000100100000000000000001111111111000011ULL,
         0b0000000001000000000000000000100100000000000000001111111111000101ULL,
         0b0000000001000000000000000000100100000000000000001111111111000110ULL,
         0b0000000001000000000000000000100100000000000000001111111101000011ULL,
         0b0000000001000000000000000000100100000000000000001111111101000101ULL,
         0b0000000001000000000000000000100100000000000000001111111101000110ULL,
         0b0000000001000000000000000000100100000000000000001111111110000011ULL,
         0b0000000001000000000000000000100100000000000000001111111110000101ULL,
         0b0000000001000000000000000000100100000000000000001111111110000110ULL});
}

TEST_CASE("SelectionEnumerator-of-selections", "[bitset]")
{
    auto a = SelectionEnumerator::bitNumbers(2, {0, 1, 2});
    auto b = SelectionEnumerator::bitNumbers(2, {0x10, 0x11, 0x12});
    auto c = SelectionEnumerator::bitNumbers(2, {0x20, 0x21, 0x22});
    SelectionEnumerator composite(std::make_shared<PermutationEnumerator>(2, 3),
                                  {a, b, c});
    expect_bitsets(
        composite,
        {
            0b0000000000000000000000000000000000000000000000110000000000000011ULL,
            0b0000000000000000000000000000000000000000000000110000000000000101ULL,
            0b0000000000000000000000000000000000000000000000110000000000000110ULL,
            0b0000000000000000000000000000000000000000000001010000000000000011ULL,
            0b0000000000000000000000000000000000000000000001010000000000000101ULL,
            0b0000000000000000000000000000000000000000000001010000000000000110ULL,
            0b0000000000000000000000000000000000000000000001100000000000000011ULL,
            0b0000000000000000000000000000000000000000000001100000000000000101ULL,
            0b0000000000000000000000000000000000000000000001100000000000000110ULL,
            0b0000000000000000000000000000001100000000000000000000000000000011ULL,
            0b0000000000000000000000000000001100000000000000000000000000000101ULL,
            0b0000000000000000000000000000001100000000000000000000000000000110ULL,
            0b0000000000000000000000000000010100000000000000000000000000000011ULL,
            0b0000000000000000000000000000010100000000000000000000000000000101ULL,
            0b0000000000000000000000000000010100000000000000000000000000000110ULL,
            0b0000000000000000000000000000011000000000000000000000000000000011ULL,
            0b0000000000000000000000000000011000000000000000000000000000000101ULL,
            0b0000000000000000000000000000011000000000000000000000000000000110ULL,
            0b0000000000000000000000000000001100000000000000110000000000000000ULL,
            0b0000000000000000000000000000001100000000000001010000000000000000ULL,
            0b0000000000000000000000000000001100000000000001100000000000000000ULL,
            0b0000000000000000000000000000010100000000000000110000000000000000ULL,
            0b0000000000000000000000000000010100000000000001010000000000000000ULL,
            0b0000000000000000000000000000010100000000000001100000000000000000ULL,
            0b0000000000000000000000000000011000000000000000110000000000000000ULL,
            0b0000000000000000000000000000011000000000000001010000000000000000ULL,
            0b0000000000000000000000000000011000000000000001100000000000000000ULL,
        });
}
