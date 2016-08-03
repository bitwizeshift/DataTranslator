/**
 * \file DataTranslatorTest
 *
 * \brief Test cases for the data translator
 *
 * \todo Clean up tests
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include "catch.hpp"

#include <iostream>
#include <DataTranslator.hpp>

#include "DummyTranslator.hpp"

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

//----------------------------------------------------------------------------
// Add Members
//----------------------------------------------------------------------------

TEST_CASE("members") {
  SECTION("Empty DataTranslator has no members")
  {
    ExampleTranslator translator;
    REQUIRE( translator.members() == 0 );
  }

  SECTION("DataTranslator has members")
  {
    ExampleTranslator translator;
    translator.add_member("scalar.bool", &ExampleClass::bool_scalar);
    REQUIRE( translator.members() == 1 );
  }
}

TEST_CASE("has_member") {
  SECTION("DataTranslator does not have member")
  {
    ExampleTranslator translator;
    REQUIRE( translator.has_member("nomember") == false );
  }

  SECTION("DataTranslator has member")
  {
    ExampleTranslator translator;
    translator.add_member("scalar.bool", &ExampleClass::bool_scalar);
    REQUIRE( translator.has_member("scalar.bool") == true );
  }
}

// 'add_member' is an overload that calls into the verbose
// member functions below.
TEST_CASE("add_member") {

  // Scalar members

  SECTION("add_bool_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("scalar.bool");
    translator.add_bool_member("scalar.bool", &ExampleClass::bool_scalar);
    bool has_member_after = translator.has_member("scalar.bool");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  SECTION("add_int_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("scalar.int");
    translator.add_int_member("scalar.int", &ExampleClass::int_scalar);
    bool has_member_after = translator.has_member("scalar.int");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  SECTION("add_float_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("scalar.float");
    translator.add_float_member("scalar.float", &ExampleClass::float_scalar);
    bool has_member_after = translator.has_member("scalar.float");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  SECTION("add_string_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("scalar.string");
    translator.add_string_member("scalar.string", &ExampleClass::string_scalar);
    bool has_member_after = translator.has_member("scalar.string");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  // Vector members

  SECTION("add_bool_vector_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("vector.bool");
    translator.add_bool_vector_member("vector.bool", &ExampleClass::bool_vector);
    bool has_member_after = translator.has_member("vector.bool");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  SECTION("add_int_vector_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("vector.int");
    translator.add_int_vector_member("vector.int", &ExampleClass::int_vector);
    bool has_member_after = translator.has_member("vector.int");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  SECTION("add_float_vector_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("vector.float");
    translator.add_float_vector_member("vector.float", &ExampleClass::float_vector);
    bool has_member_after = translator.has_member("vector.float");

    REQUIRE( (!has_member_before && has_member_after) );
  }

  SECTION("add_string_vector_member adds an entry")
  {
    ExampleTranslator translator;

    bool has_member_before = translator.has_member("vector.string");
    translator.add_string_vector_member("vector.string", &ExampleClass::string_vector);
    bool has_member_after = translator.has_member("vector.string");

    REQUIRE( (!has_member_before && has_member_after) );
  }

}

TEST_CASE("translate") {

  const ExampleTranslator translator = ExampleTranslator()
    .add_member("scalar.bool", &ExampleClass::bool_scalar)
    .add_member("scalar.int", &ExampleClass::int_scalar)
    .add_member("scalar.float", &ExampleClass::float_scalar)
    .add_member("scalar.string", &ExampleClass::string_scalar)
    .add_member("vector.bool", &ExampleClass::bool_vector)
    .add_member("vector.int", &ExampleClass::int_vector)
    .add_member("vector.float", &ExampleClass::float_vector)
    .add_member("vector.string", &ExampleClass::string_vector);

  ExampleClass example;

  translator.translate(&example, DummyTranslator());

  SECTION("translates correct number of entries") {

    SECTION("translate translates 5 boolean vector entries") {
      REQUIRE((example.bool_vector.size() == DummyTranslator::bool_vector.size()));
    }

    SECTION("translate translates 5 integral vector entries") {
      REQUIRE((example.int_vector.size() == DummyTranslator::int_vector.size()));
    }

    SECTION("translate translates 5 float vector entries") {
      REQUIRE((example.float_vector.size() == DummyTranslator::float_vector.size()));
    }

    SECTION("translate translates 5 string vector entries") {
      REQUIRE((example.string_vector.size() == DummyTranslator::string_vector.size()));
    }

  } // translates correct number of entries

  SECTION("translates correct scalar entries") {

    SECTION("translate translates scalar boolean entries correctly") {
      REQUIRE(example.bool_scalar == DummyTranslator::bool_value);
    }

    SECTION("translate translates scalar int entries correctly") {
      REQUIRE(example.int_scalar == DummyTranslator::int_value);
    }

    SECTION("translate translates scalar float entries correctly") {
      REQUIRE(example.float_scalar == DummyTranslator::float_value);
    }

    SECTION("translate translates scalar string entries correctly") {
      REQUIRE(example.string_scalar == DummyTranslator::string_value);
    }

  } // translates correct scalar entries

  SECTION("translates correct vector entries") {

    SECTION("translate translates boolean vector entries correctly") {
      bool result = true;

      for(std::size_t i = 0; i < example.bool_vector.size(); ++i) {
        result &= (example.bool_vector[i]==DummyTranslator::bool_vector[i]);
      }
      REQUIRE( result );
    }

    SECTION("translate translates integral vector entries correctly") {
      bool result = true;

      for(std::size_t i = 0; i < example.bool_vector.size(); ++i) {
        result &= (example.int_vector[i]==DummyTranslator::int_vector[i]);
      }
      REQUIRE( result );
    }

    SECTION("translate translates float vector entries correctly") {
      bool result = true;

      for(std::size_t i = 0; i < example.bool_vector.size(); ++i) {
        result &= (example.float_vector[i]==DummyTranslator::float_vector[i]);
      }
      REQUIRE( result );
    }

    SECTION("translate translates string vector entries correctly") {
      bool result = true;

      for(std::size_t i = 0; i < example.bool_vector.size(); ++i) {
        result &= (example.string_vector[i]==DummyTranslator::string_vector[i]);
      }
      REQUIRE( result );
    }
  } // translates correct vector entries
}

