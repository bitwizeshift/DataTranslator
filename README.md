#Data Translator
[![Build Status](https://travis-ci.org/bitwizeshift/DataTranslator.svg?branch=master)](https://travis-ci.org/bitwizeshift/DataTranslator)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://bitwizeshift.github.io/DataTranslator)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/bitwizeshift/DataTranslator/master/LICENSE)
[![Compiler Support](https://img.shields.io/badge/compilers-gcc%20%7C%20clang-blue.svg)]()

##What is Data Translator?

`DataTranslator` is a simple way of translating serialized data into C++ structures. 
Normally, translating data from nodes retrieved from deserializing libraries requires 
a lot of boiler-plate code, and can become even more cumbersome to translate into each
individual member of a given `struct` or `class`. 

`DataTranslator` relieves the burden by abstracting away the concept of a data node, 
and allowing for seamless translation of multiple objects at a time!

**Note**: This is a standalone implementation of the original DataTranslator found in the [Serial](https://github.com/bitwizeshift/Serial) repository. 

##Features

- Written in modern C++11 code 
- Compatible with most major compilers
- Compatible with most major deserializing libraries, such as **YamlCpp**, **RapidXML**, **RapidJSON**, - Implementation is fast and lightweight to allow for quick translation of types
- Highly configurable, enabling support for almost any fundamental member type
- Supports translation of both scalar members and vector members of a given type
etc. (Requires a "Translation Scheme" described later)
- Can translate single entries, uniform copying of multiple entries, and groups of entries at a single time

##Use

###Getting Started

The single header file, `DataTranslator.hpp` is in the `include` directory. 
Simply include this file with 

```c++
#include <DataTranslator.hpp>
```

to begin working with this library. See below for constructing `DataTranslator` classes

**Note** Make sure that the compiler is using c++11 or greater in order for this to work 
(the library will fail with a message stating as such otherwise).

###Constructing a `DataTranslator`

`serial::DataTranslator` is a templated class that requires at least one argument _T_ for the 
`struct` or `class` that will be populated.

I recommend using type aliasing to simplify the name (or `typedef` if you're old-school):

```c++
// Translates the struct/class 'ExampleClass'
using ExampleDataTranslator = serial::DataTranslator<ExampleClass>; 

auto translator = ExampleDataTranslator();
 ```

To specify the data members that are to be translated within the specified class, make 
calls to `add_member` supplying the name of the configuration node from the serialized library,
and the pointer-to-members of that object to be translated. Calls to `add_member` can be chained
in order to create a single `const` instance of a `DataTranslator.


The configuration node name can be any arbitrary type (normally a string) to retrieve a configuration value from a given deserialized node. For example, this could be an XPath string for an XML node type, or a configuration string for a `YAML::Node` from YamlCpp. How this string is managed is determined
by the Translation Scheme (explained below) and the underlying node type.

####Example

```c++
struct ExampleClass 
{
  bool        my_bool;
  int         my_int;
  float       my_float;
  std::string my_string;
};

typedef DataTranslator<ExampleClass> ExampleTranslator;

const ExampleTranslator translator = ExampleTranslator()
  .add_member("my.bool", &ExampleClass::my_bool)
  .add_member("my.int", &ExampleClass::my_int)
  .add_member("my.float", &ExampleClass::my_float)
  .add_member("my.string", &ExampleClass::my_string);
```

###Using custom types (Advanced)

If the default types of `bool`, `int`, `float`, `std::string` don't work for the translated types,
this is all configurable by further template arguments

The template arguments are, in order:

| Type      | Description                                                         |
|-----------|---------------------------------------------------------------------|
| `T`       | The type to translate. This is a required template                  |
| `BoolT`   | The type to translate as a boolean (default: `bool`)                |
| `IntT`    | The type to translate as an integer (default: `int`)                |
| `FloatT`  | The type to translate as a floating point number (default: `float`) |
| `StringT` | The type to translate as a string (default: `std::string`)          |
| `KeyT`    | The type to use for keys (default: `std::string`)                   |

This allows for customization when using different frameworks, or dealing with integral/floating point sizes outside of the defaults.

For example, if working with the windows API, the following can be done for translations:

####Example

```c++
struct Win32Struct
{
  BOOL         my_bool;
  DWORD        my_int
  double       my_float;
  std::wstring my_string;
};

using Win32StructTranslator = DataTranslator<Win32Struct,
                                             BOOL,
											                       DWORD,
											                       double,
											                       std::wstring,
											                       std::wstring>;
```

If a situation occurs where two types are the same (in the previous example, `BOOL` is normally implemented as `int`), then the calls can be disambiguated by using the _verbose_ loader functions
in order to be explicit.

The verbose loaders are identical to the `add_member` call, except that it is not overloaded.

####Example

```c++
Win32StructTranslator translator = Win32StructTranslator()
  .add_bool_member(L"my.bool", &Win32Struct::my_bool)
  .add_int_member(L"my.int", &Win32Struct::my_int)
  .add_float_member(L"my.int", &Win32Struct::my_int)
  .add_string_member(L"my.string", &Win32Struct::my_string);
  // first params are wide string because KeyT is std::wstring
```

###Creating a Translation Scheme class

A translation scheme class needs to satisfy a very simple set of functionalities. 

There are two types of translation schemes:
 - `ScalarTranslationScheme` used for translating single entries at a time
 - `SequenceTranslationScheme` used for translating sequences of entries.
 
**Note**: It is up to the implementation of Translation Scheme as to how to handle error 
cases, such as a value being requested by an incorrect type. This is to allow for native
exceptions to be caught/thrown depending on the type wrapped by the translation scheme.

####ScalarTranslationScheme Concept

#####Requirements

- **T** Translator Type;
- **t** object of type **const T**.

#####Functions

| expression                           | return                       | semantics                                                                                                                                               |
|--------------------------------------|------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|
| `t.size( name )`                     | convertible to `std::size_t` | Determines the size of a non-scalar node with the given `name`. This is undefined for scalar types.                                                     |
| `t.has( name )`                  | convertible to `bool`        | Returns `true` if `t` contains a node with the given name                                                                                         |
| `t.as_bool( name )`                  | convertible to `BoolT`       | Returns the result of the node with identifier `name` if it exists. Behavior is undefined otherwise.                                                    |
| `t.as_int( name )`                   | convertible to `IntT`        | Returns the result of the node with identifier `name` if it exists. Behavior is undefined otherwise.                                                    |
| `t.as_float( name )`                 | convertible to `FloatT`      | Returns the result of the node with identifier `name` if it exists. Behavior is undefined otherwise.                                                    |
| `t.as_string( name )`                | convertible to `StringT`     | Returns the result of the node with identifier `name` if it exists. Behavior is undefined otherwise.                                                    |
| `t.as_bool_sequence( name, func )`   | void                         | Iterates all entries in the node with identifier `name` if it exists, calling `func` on each entry. Argument to `func` must be convertible to `BoolT`   |
| `t.as_int_sequence( name, func )`    | void                         | Iterates all entries in the node with identifier `name` if it exists, calling `func` on each entry. Argument to `func` must be convertible to `IntT`    |
| `t.as_float_sequence( name, func )`  | void                         | Iterates all entries in the node with identifier `name` if it exists, calling `func` on each entry. Argument to `func` must be convertible to `FloatT`  |
| `t.as_string_sequence( name, func )` | void                         | Iterates all entries in the node with identifier `name` if it exists, calling `func` on each entry. Argument to `func` must be convertible to `StringT` |

* A `Translator` must have all functions marked as `const`.

As long as a translator supports these functions, it can be used with the `DataTranslator` to translate data to a `struct` or `class`. This would normally
be done in the form of a wrapper around the node returned by the deserialization library of your choice.

#####Example

An example dummy translator class that can only convert boolean with identifier "b" to `true`,
integer "i" to `42`, float "f" to `3.14`, and `std::string` "s" to "hello world".

```c++
class DummyTranslator {
public:
  std::size_t size(std::string) const{ return 0; }

  bool has(std::string x) const{ return true; }

  bool        as_bool(std::string) const{ return true; }
  int         as_int(std::string) const{ return 42; }
  float       as_float(std::string) const{ return 3.14; }
  std::string as_string(std::string) const{ return "hello world"; }

  template<typename Func>
  void as_bool_sequence(std::string, Func) const{}

  template<typename Func>
  void as_int_sequence(std::string, Func) const{}

  template<typename Func>
  void as_float_sequence(std::string, Func) const{}

  template<typename Func>
  void as_string_sequence(std::string, Func) const{}
};
```

To create a more complicated translator, you can write a wrapper around the desired node
type, such as mapping `YAML::Node`'s `as<int>()` to `as_int()`.

####SequenceTranslationScheme

#####Requirements

- **T** Translator Type;
- **t** object of type **T**.

#####Relationship

- `SequenceTranslationScheme` is also a `ScalarTranslationScheme`.

#####Functions

| expression                           | return                       | semantics                                                                                                                                               |
|--------------------------------------|------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|
| `t.next()`                     | convertible to `bool` | Iterates to the next entry in the sequence, if one exists. returns `true` if there is an entry, `false` otherwise.                                                     |

### Complete Example

Using the `DummyTranslator` class above, mixed with parts from the first example example:

```c++
#include <iostream>
struct ExampleClass 
{
  bool        my_bool;
  int         my_int;
  float       my_float;
  std::string my_string;
};

typedef DataTranslator<ExampleClass> ExampleTranslator;

const ExampleTranslator translator = ExampleTranslator()
  .add_member("b", &ExampleClass::my_bool)    // translate "b" -> true
  .add_member("i", &ExampleClass::my_int)     // translate "i" -> 42
  .add_member("f", &ExampleClass::my_float)   // translate "f" -> 3.14
  .add_member("s", &ExampleClass::my_string); // translate "s" -> "hello world"
  
int main()
{
  ExampleClass example; // construct a class, no initialization

  translator.translate(&example, DummyTranslator());

  std::cout << example.my_bool << "\n"
            << example.my_int  << "\n"
            << example.my_float << "\n"
            << example.my_string << "\n";

  return 0;  
}
```

The above example, when compiled with `gcc 5.3.0` is the following:

```
1
42
3.14
hello world
```

### Further Examples

Below are some fully implemented translation scheme examples wrapper around 
existing deserialization libraries:

```todo: upload examples```

## Tested Compilers

The following compilers are currently being tested through continuous integration with [Travis](https://travis-ci.org/bitwizeshift/DataTranslator).

| Compiler        | Operating System                   |
|-----------------|------------------------------------|
| g++ 4.8.5       | Ubuntu 14.04.1 TLS                 |
| g++ 4.9.3       | Ubuntu 14.04.4 TLS                 |
| g++ 5.3.0       | Ubuntu 14.04.4 TLS                 |
| g++ 6.1.1       | Ubuntu 14.04.1 TLS                 |
| clang 3.5.0     | Ubuntu 14.04.1 TLS                 |
| clang 3.6.2     | Ubuntu 14.04.1 TLS                 |
| clang xcode 6.0 | Darwin Kernel 13.4.0 (OSX 10.9.5)  |
| clang xcode 6.1 | Darwin Kernel 14.3.0 (OSX 10.9.5)  |
| clang xcode 7.0 | Darwin Kernel 14.5.0 (OSX 10.10.5) |
| clang xcode 7.3 | Darwin Kernel 15.5.0 (OSX 10.11.5) |
| clang xcode 8.0 | Darwin Kernel 15.6.0 (OSX 10.11.5) |

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2016 [Matthew Rodusek](http://rodusek.me/)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.