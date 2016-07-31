/**
 * \file concepts.hpp
 *
 * \brief This header contains concept definitions for the translator types.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef DATATRANSLATOR_CONCEPTS_HPP_
#define DATATRANSLATOR_CONCEPTS_HPP_

#include <type_traits>

#include "detail/concepts.inl"

namespace serial {
  namespace concepts {

    //////////////////////////////////////////////////////////////////////////
    /// \class serial::concepts::ScalarTranslationScheme
    ///
    /// \brief The concept for a scalar translation scheme
    ///
    /// Required Functions:
    ///
    /// - std::size_t size(string) const
    ///
    /// - bool has(string) const;
    ///
    /// - bool_type as_bool(string) const;
    /// - int_type as_int(string) const;
    /// - float_type as_float(string) const;
    /// - string_type as_string(string) const;
    ///
    /// - void as_bool_sequence(string, Func) const;
    /// - void as_int_sequence(string, Func) const;
    /// - void as_float_sequence(string, Func) const;
    /// - void as_string_sequence(string, Func) const;
    ///
    /// \tparam Translator the translation scheme to check
    /// \tparam BoolT      the type to use for boolean types
    /// \tparam IntT       the type to use for integral types
    /// \tparam FloatT     the type to use for floating point types
    /// \tparam StringT    the type to use for string types
    /// \tparam KeyStringT the type to use for key strings
    //////////////////////////////////////////////////////////////////////////
    template<
      typename Translator,
      typename BoolT,
      typename IntT,
      typename FloatT,
      typename StringT,
      typename KeyStringT
    >
    struct ScalarTranslationScheme
    {
      constexpr ScalarTranslationScheme(){}

      static_assert(ScalarTranslationScheme_size<Translator,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'size(str)' to return a type convertible to std::size_t");
      static_assert(ScalarTranslationScheme_has<Translator,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'has(str)' to return a type convertible to bool");

      static_assert(ScalarTranslationScheme_as_bool<Translator,BoolT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_bool(str)' to return a type convertible to BoolT");
      static_assert(ScalarTranslationScheme_as_int<Translator,IntT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_int(str)' to return a type convertible to IntT");
      static_assert(ScalarTranslationScheme_as_float<Translator,FloatT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_float(str)' to return a type convertible to FloatT");
      static_assert(ScalarTranslationScheme_as_string<Translator,StringT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_string(str)' to return a type convertible to StringT");

      static_assert(ScalarTranslationScheme_as_bool_sequence<Translator,BoolT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_bool_sequence(str,func)' to accept a function that takes 'BoolT' as argument");
      static_assert(ScalarTranslationScheme_as_int_sequence<Translator,IntT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_int_sequence(str,func)' to accept a function that takes 'IntT' as argument");
      static_assert(ScalarTranslationScheme_as_float_sequence<Translator,FloatT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_float_sequence(str,func)' to accept a function that takes 'FloatT' as argument");
      static_assert(ScalarTranslationScheme_as_string_sequence<Translator,StringT,KeyStringT>::value,"ScalarTranslationScheme concept requires const function 'as_string_sequence(str,func)' to accept a function that takes 'StringT' as argument");
    };

    //////////////////////////////////////////////////////////////////////////
    /// \class serial::concepts::SequenceTranslationScheme
    ///
    /// \brief The concept for a Sequence translation scheme
    ///
    /// Required Functions:
    ///
    /// - std::size_t size(string) const
    ///
    /// - bool next();
    ///
    /// \tparam Translator the translation scheme to check
    /// \tparam BoolT      the type to use for boolean types
    /// \tparam IntT       the type to use for integral types
    /// \tparam FloatT     the type to use for floating point types
    /// \tparam StringT    the type to use for string types
    /// \tparam KeyStringT the type to use for key strings
    //////////////////////////////////////////////////////////////////////////
    template<
      typename Translator,
      typename BoolT,
      typename IntT,
      typename FloatT,
      typename StringT,
      typename KeyStringT
    >
    struct SequenceTranslationScheme : ScalarTranslationScheme<Translator,
                                                               BoolT,
                                                               IntT,
                                                               FloatT,
                                                               StringT,
                                                               KeyStringT>
    {
      constexpr SequenceTranslationScheme(){}

      static_assert(SequenceTranslationScheme_next<Translator>::value,"SequenceTranslationScheme concept requires non-const function 'next()' to return a type convertible to bool");
    };

  } // namespace concepts
} // namespace serial

#endif /* INCLUDE_CONCEPTS_HPP_ */
