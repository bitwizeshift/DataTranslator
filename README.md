# Data Translator (Standalone)

This is a standalone implementation of the original DataTranslator found in the [Serial](https://github.com/bitwizeshift/Serial) repository. 
This `DataTranslator` supports translation between any arbitrary data node (such as a node received from `RapidXML`, `RapidJson`, `YamlCpp`, etc)
by providing a Translation scheme.

## Features

- Compatible with C++11 and above
- Translation of arbitrary deserialized data through use of an adapter
- Configurable value types, allowing custom pointer-to-members to be used
- Support for both scalar values and sequences of entires through `std::vector`
- Lightweight implementation to allow for quick translation of types 

## How It Works

## Use

### Constructing a `DataTranslator`

To construct a data translator, include the hader and construct a `DataTranslator` templated on the type of the `struct` or `class` to translate. 
Then, make calls to `add_member` supplying the configuration name and the pointer-to-members that are to be translated. 

Calls to `add_member` can be chained in order to create a single `const` instance of a `DataTranslator`.

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

### Using custom types

If the default types of `bool`, `int`, `float`, `std::string` don't work for the specific purpose, or if the string for the configuration
nodes needs to be of a different type, all of these are configurable by template arguments. 

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

typedef DataTranslator<Win32Struct,
                       BOOL,
                       DWORD,
                       double,
                       std::wstring,
                       std::wstring> Win32StructTranslator;
```

If a situation occurs where two types are the same (in the previous example, `BOOL` is normally implemented as `int`), then the unambiguous/verbose
member loaders are required to disambiguate the call. 

####Example

```c++
Win32StructTranslator translator = Win32StructTranslator()
  .add_bool_member(L"my.bool", &Win32Struct::my_bool)
  .add_int_member(L"my.int", &Win32Struct::my_int)
  .add_float_member(L"my.int", &Win32Struct::my_int)
  .add_string_member(L"my.string", &Win32Struct::my_string);
  // first params are wide string because KeyT is std::wstring
```

### Creating a Translator class

A translator class needs to satisfy a very simple set of functionalities. 

The Translator concept is:

####Requirements

- **T** Translator Type;
- **t** object of type **const T**.

####Functions

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

#### Example

An example dummy translator class that can only convert boolean with identifier "b" to `true`,
integer "i" to `42`, float "f" to `3.14`, and `std::string` "s" to "hello world".

```c++
class DummyTranslator {
public:
  std::size_t size(std::string) const{ return 0; }

  bool has_bool(std::string x) const{ return x=="b"; }
  bool has_int(std::string x) const{ return x=="i"; }
  bool has_float(std::string x) const{ return x=="f"; }
  bool has_string(std::string x) const{ return x=="s"; }

  bool has_bool_sequence(std::string ) const{ return false; }
  bool has_int_sequence(std::string ) const{ return false; }
  bool has_float_sequence(std::string ) const{ return false; }
  bool has_string_sequence(std::string ) const{ return false; }

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

## Todo

- Support array and vector translations