/* 
 * File:   test.cpp
 * Author: nsamson
 *
 * Created on October 7, 2015, 6:19 PM
 */

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include "lexer.hpp"
#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test_framework;

//test_suite*
//init_unit_test_suite( int, char* [] ) {
//    test_suite* test= BOOST_TEST_SUITE( "Unit test example 1" );
//
//    // this example will pass cause we know ahead of time number of expected failures
//    test->add( BOOST_TEST_CASE( &free_test_function ), 1 /* expected one error */ );
//
//    return test;
//}

BOOST_AUTO_TEST_SUITE(lexer_tests)
        
BOOST_AUTO_TEST_CASE(token_test_1) {
    auto tokenizer = pixie::compile::PixieTokenizer("11.0 if True else False");
    BOOST_REQUIRE_EQUAL(std::distance(tokenizer.begin(), tokenizer.end()), 5);
    pixie::compile::token_vec tokens;
    tokens.insert(tokens.end(), tokenizer.begin(), tokenizer.end());

    BOOST_CHECK(tokens[0].has_value == true);
    BOOST_CHECK(tokens[1].has_value == false);
    BOOST_CHECK(tokens[2].has_value == false);
    BOOST_CHECK(tokens[3].has_value == false);
    BOOST_CHECK(tokens[4].has_value == false);
    
    BOOST_CHECK(tokens[0].type == pixie::compile::PixieTokenType::Float);
    BOOST_CHECK(tokens[1].type == pixie::compile::PixieTokenType::If);
    BOOST_CHECK(tokens[2].type == pixie::compile::PixieTokenType::True);
    BOOST_CHECK(tokens[3].type == pixie::compile::PixieTokenType::Else);
    BOOST_CHECK(tokens[4].type == pixie::compile::PixieTokenType::False);
    
}

BOOST_AUTO_TEST_CASE(token_test_2_literals) {
    auto tokenizer = pixie::compile::PixieTokenizer(
            R"("This is a double-quoted string! With a \" at both ends!")");
    
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::QString);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"("This is a double-quoted string! With a \" at both ends!")"));
    
    tokenizer = pixie::compile::PixieTokenizer(
            R"('This is a single-quoted string! With a \' at both ends!')");
    
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::AString);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"('This is a single-quoted string! With a \' at both ends!')"));
    
    tokenizer = pixie::compile::PixieTokenizer(
            R"(5.0E10)");
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::Float);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"(5.0E10)"));
    
    tokenizer = pixie::compile::PixieTokenizer(
            R"(200)");
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::DecimalInteger);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"(200)"));
    
    tokenizer = pixie::compile::PixieTokenizer(
            R"(0o1234567)");
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::OctalInteger);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"(0o1234567)"));
    
    tokenizer = pixie::compile::PixieTokenizer(
            R"(0b10100101)");
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::BinaryInteger);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"(0b10100101)"));
    
    tokenizer = pixie::compile::PixieTokenizer(
            R"(0x0123456789abcdefABCDEF)");
    BOOST_CHECK(tokenizer.begin()->type == pixie::compile::PixieTokenType::HexadecimalInteger);
    BOOST_CHECK(
            tokenizer.begin()->value == std::string(
            R"(0x0123456789abcdefABCDEF)"));
}

BOOST_AUTO_TEST_SUITE_END()
