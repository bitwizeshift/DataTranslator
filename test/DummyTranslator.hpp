/**
 * @file DummyTranslator.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Aug 3, 2016
 *
 */
#ifndef TEST_DUMMYTRANSLATOR_HPP_
#define TEST_DUMMYTRANSLATOR_HPP_

#include <string>
#include <vector>

class DummyTranslator
{
public:

  static const bool        bool_value;
  static const int         int_value;
  static const float       float_value;
  static const std::string string_value;

  static const std::vector<bool>        bool_vector;
  static const std::vector<int>         int_vector;
  static const std::vector<float>       float_vector;
  static const std::vector<std::string> string_vector;

  std::size_t size(const std::string&) const{ return 5; }

  bool has(const std::string& x) const{ return true; }

  bool        as_bool(const std::string&) const{ return bool_value; }
  int         as_int(const std::string&) const{ return int_value; }
  float       as_float(const std::string&) const{ return float_value; }
  std::string as_string(const std::string&) const{ return string_value; }

  template<typename Func>
  void as_bool_sequence(std::string, Func func) const
  {
    for(bool b : bool_vector) {
      func(b);
    }
  }

  template<typename Func>
  void as_int_sequence(std::string, Func func) const
  {
    for(int i : int_vector) {
      func(i);
    }
  }

  template<typename Func>
  void as_float_sequence(std::string, Func func) const
  {
    for(float f : float_vector) {
      func(f);
    }
  }

  template<typename Func>
  void as_string_sequence(std::string, Func func) const
  {
    for(const auto& s : string_vector) {
      func(s);
    }
  }

};

#endif /* TEST_DUMMYTRANSLATOR_HPP_ */
