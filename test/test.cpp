/**
 * @file test.cpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jul 7, 2016
 *
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <DataTranslator.hpp>

struct ExampleClass
{
  bool        bool_scalar;
  int         int_scalar;
  float       float_scalar;
  std::string string_scalar;

  std::vector<bool>        bool_vector;
  std::vector<int>         int_vector;
  std::vector<float>       float_vector;
  std::vector<std::string> string_vector;
};

typedef serial::DataTranslator<ExampleClass> ExampleTranslator;

const ExampleTranslator translator = ExampleTranslator()
  .add_member("scalar.bool", &ExampleClass::bool_scalar)
  .add_member("scalar.int", &ExampleClass::int_scalar)
  .add_member("scalar.float", &ExampleClass::float_scalar)
  .add_member("scalar.string", &ExampleClass::string_scalar)
  .add_member("vector.bool", &ExampleClass::bool_vector)
  .add_member("vector.int", &ExampleClass::int_vector)
  .add_member("vector.float", &ExampleClass::float_vector)
  .add_member("vector.string", &ExampleClass::string_vector);

BOOST_AUTO_TEST_CASE( ptr_is_convertible_to_void_and_back )
{

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_5_neg_5_equals_0 )
{
    BOOST_CHECK( true );
}
