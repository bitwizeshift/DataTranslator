/**
 * \file DataTranslator
 *
 * \brief This is the main header for the DataTranslator standalone library.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef DATATRANSLATOR_HPP_
#define DATATRANSLATOR_HPP_

#if __cplusplus < 201103L
# error This file requires compiler and library support for the ISO C++11 standard.
#endif

#include <unordered_map>
#include <string>
#include <cstring>
#include <vector>

//
// Concept: ScalarTranslator
//
// Required Functions:
//
// - std::size_t size(string) const
//
// - bool has(string) const;
//
// - bool_type   as_bool(string) const;
// - int_type    as_int(string) const;
// - float_type  as_float(string) const;
// - string_type as_string(string) const;
//
// - void as_bool_sequence(string, Func) const;
// - void as_int_sequence(string, Func) const;
// - void as_float_sequence(string, Func) const;
// - void as_string_sequence(string, Func) const;
//

namespace serial {

  ////////////////////////////////////////////////////////////////////////////
  /// \class serial::DataTranslator
  ///
  /// \brief Translates data from a given data bin into the supplied \p T type.
  ///
  /// The types to translate into can optionally be specified as template
  /// arguments, allowing for things like BOOL from the WinAPI to be used
  /// in place of the built-in bool.
  ///
  /// In the event that two types are the same (e.g. BoolT = BOOL (int),
  /// IntT = int), then the unambiguous member loaders are needed instead
  /// of the normal #add_member member functions.
  ///
  /// Example use:
  /// \code
  /// const DataTranslator<MyStruct> translator = DataTranslator<MyStruct>()
  ///   .add_member("my.entry",&MyStruct::entry)
  ///   .add_member("my.other.entry",&MyStruct::other_entry)
  ///   ...
  ///   .add_member("my.last.entry",&MyStruct::last_entry);
  ///
  /// MyStruct to_be_populated;
  /// translator.translate(&to_be_populated, SomeTranslator(data));
  /// \endcode
  ///
  /// The type of string used for keys is optionally configurable with
  /// the KeyS argument. This is necessary for supporting UTF strings
  ///
  /// \tparam T          The type to translate into
  /// \tparam BoolT      the type to use for boolean values
  /// \tparam IntT       The type to use for integral values
  /// \tparam FloatT     The type to use for floating point values
  /// \tparam StringT    The type to use for string values
  /// \tparam KeyStringT The type to use for key strings
  ////////////////////////////////////////////////////////////////////////////
  template<typename T,
           typename BoolT   = bool,
           typename IntT    = int,
           typename FloatT  = float,
           typename StringT = std::string,
           typename KeyStringT = std::string>
  class DataTranslator final
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    typedef DataTranslator<T,BoolT,IntT,FloatT,StringT,KeyStringT> this_type;

    typedef T           value_type;      ///< Type of this Data Translator
    typedef T*          pointer;         ///< Type representing pointer
    typedef const T*    const_pointer;   ///< Type representing constant pointer
    typedef T&          reference;       ///< Type representing reference
    typedef const T&    const_reference; ///< Type representing constant reference
    typedef std::size_t size_type;       ///< Size type

    // Member Types
    typedef BoolT      bool_type;       ///< The type to use for boolean values
    typedef IntT       int_type;        ///< The type to use for integer values
    typedef FloatT     float_type;      ///< The type to use for float values
    typedef StringT    string_type;     ///< The type to use for string literals.
    typedef KeyStringT key_string_type; ///< The type to use for the key strings

    // Member pointers to scalar types
    typedef bool_type   value_type::*bool_member;  ///< Class pointer to bool member
    typedef int_type    value_type::*int_member;   ///< Class pointer to long member
    typedef float_type  value_type::*float_member; ///< Class pointer to float member
    typedef string_type value_type::*string_member;///< Class pointer to string member

    // Member pointers to vector types
    typedef std::vector<bool_type>   value_type::*bool_vector_member;  ///< Class pointer to bool vector member
    typedef std::vector<int_type>    value_type::*int_vector_member;   ///< Class pointer to long vector member
    typedef std::vector<float_type>  value_type::*float_vector_member; ///< Class pointer to float vector member
    typedef std::vector<string_type> value_type::*string_vector_member;///< Class pointer to string vector member

    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
  public:

    /// \brief Initializes the Data Translator with the specified binary data
    DataTranslator() = default;

    //-------------------------------------------------------------------------
    // Capacity
    //-------------------------------------------------------------------------
  public:

    /// \brief Gets total number of members this \c DataTranslator will
    ///        translate
    ///
    /// \return the total number of members to translate
    size_type members() const noexcept;

    //-------------------------------------------------------------------------
    // Verbose Member Loaders
    //-------------------------------------------------------------------------
  public:

    // Scalar Types

    /// \brief Adds a boolean pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the bool pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_bool_member( const key_string_type& name,
                                bool_member member );

    /// \brief Adds an integer pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the integer pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_int_member( const key_string_type& name,
                               int_member member );

    /// \brief Adds a float pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the floating point pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_float_member( const key_string_type& name,
                                 float_member member );

    /// \brief Adds a float pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the string pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_string_member( const key_string_type& name,
                                  string_member member );

    // Vector types

    /// \brief Adds a boolean vector pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the boolean vector pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_bool_vector_member( const key_string_type& name, bool_vector_member member );

    /// \brief Adds an integral vector pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the integral vector pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_int_vector_member( const key_string_type& name, int_vector_member member );

    /// \brief Adds a floating point vector pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the floating point vector pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_float_vector_member( const key_string_type& name, float_vector_member member );

    /// \brief Adds a string vector pointer-to-member
    ///
    /// \param name the name of the configuration
    /// \param member the string vector pointer-to-member to translate
    ///
    /// \return reference to (*this) to allow chaining calls
    this_type& add_string_vector_member( const key_string_type& name, string_vector_member member );

    //-------------------------------------------------------------------------
    // Overloaded Member Loaders
    //-------------------------------------------------------------------------
  public:

    // Scalar types

    /// \copydoc DataTranslator::add_bool_member
    this_type& add_member( const key_string_type& name, bool_member member );

    /// \copydoc DataTranslator::add_int_member
    this_type& add_member( const key_string_type& name, int_member member );

    /// \copydoc DataTranslator::add_float_member
    this_type& add_member( const key_string_type& name, float_member member );

    /// \copydoc DataTranslator::add_string_member
    this_type& add_member( const key_string_type& name, string_member member );

    // Vector types

    /// \copydoc DataTranslator::add_bool_vector_member
    this_type& add_member( const key_string_type& name, bool_vector_member member );

    /// \copydoc DataTranslator::add_int_vector_member
    this_type& add_member( const key_string_type& name, int_vector_member member );

    /// \copydoc DataTranslator::add_float_vector_member
    this_type& add_member( const key_string_type& name, float_vector_member member );

    /// \copydoc DataTranslator::add_string_vector_member
    this_type& add_member( const key_string_type& name, string_vector_member member );

    //-------------------------------------------------------------------------
    // Loaders
    //-------------------------------------------------------------------------
  public:

    /// \brief Translates a data bin into a single data structure
    ///
    /// \param object The object to be populated with data
    /// \param data   The data to translate into the structures
    /// \return the number of members translated
    template<typename Translator>
    size_type translate( value_type* object, const Translator& data ) const;

    /// \brief Translates a single data bin into an array of structures
    ///
    /// \param objects Array of objects to be populated with data
    /// \param size    The size of the array to translate
    /// \param data    The binary data to translate into the structure
    /// \return the number of members translated in one entry
    template<typename Translator>
    size_type translate_uniform( value_type* objects,
                                 size_type size,
                                 const Translator& data ) const;

    /// \brief Translates a sequence of structures into the appropriate
    ///        data type
    ///
    /// \param it the output iterator to use for insertions
    /// \param data the data to insert
    /// \return the number of members translated in all entries
    template<typename OutputIterator, typename Translator>
    size_type translate_sequence( OutputIterator it,
                                  const Translator& data ) const;

    /// \brief Translates a sequence of structures into the appropriate
    ///        data type with a bounded size
    ///
    /// \param it the output iterator to use for insertions
    /// \param size the max number of entries to translate
    /// \param data the data to insert
    /// \return the number of members translated in all entries
    template<typename OutputIterator, typename Translator>
    size_type translate_sequence( OutputIterator it,
                                  std::size_t size,
                                  const Translator& data ) const;


    //-------------------------------------------------------------------------
    // Private Member Types
    //-------------------------------------------------------------------------
  private:

    // Scalar member mapping
    typedef std::unordered_map<std::string, bool_member>   bool_member_map;
    typedef std::unordered_map<std::string, int_member>    int_member_map;
    typedef std::unordered_map<std::string, float_member>  float_member_map;
    typedef std::unordered_map<std::string, string_member> string_member_map;

    // Vector member mapping
    typedef std::unordered_map<std::string, bool_vector_member>   bool_vector_member_map;
    typedef std::unordered_map<std::string, int_vector_member>    int_vector_member_map;
    typedef std::unordered_map<std::string, float_vector_member>  float_vector_member_map;
    typedef std::unordered_map<std::string, string_vector_member> string_vector_member_map;

    //-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
  private:

    // Scalar members
    bool_member_map   m_bool_members;   ///< Map of bool member pointers
    int_member_map    m_int_members;    ///< Map of int member pointers
    float_member_map  m_float_members;  ///< Map of float member pointers
    string_member_map m_string_members; ///< Map of string member pointers

    // Vector members
    bool_vector_member_map   m_bool_vector_members;   ///< Vector of bool array member pointers
    int_vector_member_map    m_int_vector_members;    ///< Vector of int array member pointers
    float_vector_member_map  m_float_vector_members;  ///< Vector of float array member pointers
    string_vector_member_map m_string_vector_members; ///< Vector of string array member pointers

    //-------------------------------------------------------------------------
    // Private Member Functions
    //-------------------------------------------------------------------------
  private:

    /// \brief Translate all scalar entries into the specified objects
    ///
    /// \param object the object to translate data into
    /// \param data the data to translate
    ///
    /// \return the number of scalars successfully translated
    template<typename Translator>
    size_type translate_scalar_data( value_type* object,
                                     const Translator& data ) const;

    /// \brief Translate all vector entries into the specified objects
    ///
    /// \param object the object to translate data into
    /// \param data the data to translate
    ///
    /// \return the number of vector successfully translated
    template<typename Translator>
    size_type translate_vector_data( value_type* object,
                                     const Translator& data ) const;

  };

} // namespace serial

#include "detail/DataTranslator.inl"

#endif /* DATATRANSLATOR_HPP_ */
