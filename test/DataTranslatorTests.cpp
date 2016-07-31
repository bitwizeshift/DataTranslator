/**
 * \file DataTranslatorTest
 *
 * \brief Test cases for the data translator
 *
 * \todo Clean up tests
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataTranslatorTest
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

class DummyTranslator
{
public:
  std::size_t size(std::string) const{ return 5; }

  bool has(std::string x) const{ return true; }

  bool        as_bool(std::string) const{ return true; }
  int         as_int(std::string) const{ return 42; }
  float       as_float(std::string) const{ return 4.0; }
  std::string as_string(std::string) const{ return "hello world"; }

  template<typename Func>
  void as_bool_sequence(std::string, Func func) const
  {
    bool b = true;
    for(int i=0;i<5;++i)
    {
      func(b);
      b = !b;
    }
  }

  template<typename Func>
  void as_int_sequence(std::string, Func func) const
  {
    for(int i=0;i<5;++i)
    {
      func(i);
    }
  }

  template<typename Func>
  void as_float_sequence(std::string, Func func) const
  {
    for(int i=0; i<5; ++i)
    {

      func(i * 1.5);
    }
  }

  template<typename Func>
  void as_string_sequence(std::string, Func func) const
  {
    for(int i=0;i<5;i++)
    {
      func(std::to_string(i));
    }
  }

};


const ExampleTranslator translator = ExampleTranslator()
  .add_member("scalar.bool", &ExampleClass::bool_scalar)
  .add_member("scalar.int", &ExampleClass::int_scalar)
  .add_member("scalar.float", &ExampleClass::float_scalar)
  .add_member("scalar.string", &ExampleClass::string_scalar)
  .add_member("vector.bool", &ExampleClass::bool_vector)
  .add_member("vector.int", &ExampleClass::int_vector)
  .add_member("vector.float", &ExampleClass::float_vector)
  .add_member("vector.string", &ExampleClass::string_vector);

//----------------------------------------------------------------------------
// Add Members
//----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( add_bool_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("scalar.bool", &ExampleClass::bool_scalar);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_int_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("scalar.int", &ExampleClass::int_scalar);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_float_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("scalar.float", &ExampleClass::float_scalar);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_string_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("scalar.string", &ExampleClass::string_scalar);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_bool_vector_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("vector.bool", &ExampleClass::bool_vector);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_int_vector_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("vector.int", &ExampleClass::int_vector);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_float_vector_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("vector.float", &ExampleClass::float_vector);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_string_vector_member_doesnt_fail_to_compile )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("vector.string", &ExampleClass::string_vector);

  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_CASE( add_member_is_chainable )
{
  const ExampleTranslator translator = ExampleTranslator()
    .add_member("scalar.bool", &ExampleClass::bool_scalar)
    .add_member("scalar.int", &ExampleClass::int_scalar)
    .add_member("scalar.float", &ExampleClass::float_scalar)
    .add_member("scalar.string", &ExampleClass::string_scalar)
    .add_member("vector.bool", &ExampleClass::bool_vector)
    .add_member("vector.int", &ExampleClass::int_vector)
    .add_member("vector.float", &ExampleClass::float_vector)
    .add_member("vector.string", &ExampleClass::string_vector);

  BOOST_CHECK( true );
}
//----------------------------------------------------------------------------
// Scalar Translation
//----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( translates_scalar_bool )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );
  BOOST_CHECK( example.bool_scalar == true );
}

BOOST_AUTO_TEST_CASE( translates_scalar_int )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );
  BOOST_CHECK( example.int_scalar == 42 );
}

BOOST_AUTO_TEST_CASE( translates_scalar_float )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );
  BOOST_CHECK( example.float_scalar == 4.00 );
}

BOOST_AUTO_TEST_CASE( translates_scalar_string )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );
  BOOST_CHECK( example.string_scalar == "hello world" );
}

//----------------------------------------------------------------------------
// Vector Translation
//----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( translates_vector_bool )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );

  bool value = true;
  bool is_correct = example.bool_vector.size()==5;
  for(bool entry : example.bool_vector)
  {
    is_correct &= (value == entry);
    value = !value;
  }

  BOOST_CHECK( is_correct );
}

BOOST_AUTO_TEST_CASE( translates_vector_int )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );

  int value = 0;
  bool is_correct = example.int_vector.size()==5;
  for(auto& entry : example.int_vector)
  {
    is_correct &= (value == entry);
    ++value;
  }

  BOOST_CHECK( is_correct );
}

BOOST_AUTO_TEST_CASE( translates_vector_float )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );

  int value = 0;
  bool is_correct = example.float_vector.size()==5;
  for(auto& entry : example.float_vector)
  {
    is_correct &= ((value * 1.5) == entry);
    ++value;
  }

  BOOST_CHECK( is_correct );
}

BOOST_AUTO_TEST_CASE( translates_vector_string )
{
  ExampleClass example;
  translator.translate( &example, DummyTranslator() );

  int value = 0;
  bool is_correct = example.string_vector.size()==5;
  for(auto& entry : example.string_vector)
  {
    is_correct &= (std::to_string(value) == entry);
    ++value;
  }

  BOOST_CHECK( is_correct );
}
