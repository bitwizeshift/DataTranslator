#ifndef DATATRANSLATOR_DETAIL_CONCEPTS_INL_
#define DATATRANSLATOR_DETAIL_CONCEPTS_INL_

namespace serial {
  namespace concepts {

    template<typename...>
    struct voidify{ typedef void type; };

    template<typename...Args>
    using void_t = typename voidify<Args...>::type;

    //------------------------------------------------------------------------

    template<typename Translator, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_size : std::false_type{};

    template<typename T, typename KeyStringT>
    struct ScalarTranslationScheme_size<
      T,
      KeyStringT,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<const T>().size(std::declval<KeyStringT>())),
          std::size_t
        >::value>::type
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_has : std::false_type{};

    template<typename T, typename KeyStringT>
    struct ScalarTranslationScheme_has<
      T,
      KeyStringT,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<const T>().has(std::declval<KeyStringT>())),
          bool
        >::value>::type
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename BoolT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_bool : std::false_type{};

    template<typename T, typename BoolT, typename KeyStringT>
    struct ScalarTranslationScheme_as_bool<
      T,
      BoolT,
      KeyStringT,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<const T>().as_bool(std::declval<KeyStringT>())),
          BoolT
        >::value>::type
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename IntT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_int : std::false_type{};

    template<typename T, typename IntT, typename KeyStringT>
    struct ScalarTranslationScheme_as_int<
      T,
      IntT,
      KeyStringT,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<const T>().as_int(std::declval<KeyStringT>())),
          IntT
        >::value>::type
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename FloatT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_float : std::false_type{};

    template<typename T, typename FloatT, typename KeyStringT>
    struct ScalarTranslationScheme_as_float<
      T,
      FloatT,
      KeyStringT,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<const T>().as_float(std::declval<KeyStringT>())),
          FloatT
        >::value>::type
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename StringT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_string : std::false_type{};

    template<typename T, typename StringT, typename KeyStringT>
    struct ScalarTranslationScheme_as_string<
      T,
      StringT,
      KeyStringT,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<const T>().as_string(std::declval<KeyStringT>())),
          StringT
        >::value>::type
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename BoolT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_bool_sequence : std::false_type{};

    template<typename T, typename BoolT, typename KeyStringT>
    struct ScalarTranslationScheme_as_bool_sequence<
      T,
      BoolT,
      KeyStringT,
      void_t<
        decltype(std::declval<const T>().as_bool_sequence(std::declval<KeyStringT>(),std::declval<void(*)(const BoolT&)>()))
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename IntT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_int_sequence : std::false_type{};

    template<typename T, typename IntT, typename KeyStringT>
    struct ScalarTranslationScheme_as_int_sequence<
      T,
      IntT,
      KeyStringT,
      void_t<
        decltype(std::declval<const T>().as_int_sequence(std::declval<KeyStringT>(),std::declval<void(*)(const IntT&)>()))
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename FloatT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_float_sequence : std::false_type{};

    template<typename T, typename FloatT, typename KeyStringT>
    struct ScalarTranslationScheme_as_float_sequence<
      T,
      FloatT,
      KeyStringT,
      void_t<
        decltype(std::declval<const T>().as_float_sequence(std::declval<KeyStringT>(),std::declval<void(*)(const FloatT&)>()))
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename StringT, typename KeyStringT, typename = void>
    struct ScalarTranslationScheme_as_string_sequence : std::false_type{};

    template<typename T, typename StringT, typename KeyStringT>
    struct ScalarTranslationScheme_as_string_sequence<
      T,
      StringT,
      KeyStringT,
      void_t<
        decltype(std::declval<const T>().as_string_sequence(std::declval<KeyStringT>(),std::declval<void(*)(const StringT&)>()))
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename Translator, typename = void>
    struct SequenceTranslationScheme_next : std::false_type{};

    template<typename T>
    struct SequenceTranslationScheme_next<
      T,
      void_t<
        typename std::enable_if<std::is_convertible<
          decltype(std::declval<T>().next()),
          bool
        >::value>::type
      >
    > : std::true_type{};

  } // namespace concepts
} // namespace serial

#endif /* DATATRANSLATOR_DETAIL_CONCEPTS_INL_ */
