#ifndef DETAIL_DATATRANSLATOR_INL_
#define DETAIL_DATATRANSLATOR_INL_

namespace serial {

  //--------------------------------------------------------------------------
  // Verbose Loaders
  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::size_type
    DataTranslator<T,B,I,F,S,K>::members()
    const noexcept
  {
    return (m_bool_members.size() + m_bool_vector_members.size() +
            m_int_members.size()  + m_int_vector_members.size() +
            m_float_members()     + m_float_vector_members.size() +
            m_string_members()    + m_string_vector_members.size());
  }

  //--------------------------------------------------------------------------
  // Verbose Loaders
  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_bool_member( const key_string_type& name,
                                                  bool_member member )
  {
    m_bool_members[ name ] = member;
    return (*this);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_int_member( const key_string_type& name,
                                                 int_member member )
  {
    m_int_members[ name ] = member;
    return (*this);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_float_member( const key_string_type& name,
                                                   float_member member )
  {
    m_float_members[ name ] = member;
    return (*this);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_string_member( const key_string_type& name,
                                                    string_member member )
  {
    m_string_members[ name ] = member;
    return (*this);
  }

  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_bool_vector_member( const key_string_type& name,
                                                         bool_vector_member member )
  {
    m_bool_vector_members[ name ] = member;
    return (*this);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_int_vector_member( const key_string_type& name,
                                                        int_vector_member member )
  {
    m_int_vector_members[ name ] = member;
    return (*this);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_float_vector_member( const key_string_type& name,
                                                          float_vector_member member )
  {
    m_float_vector_members[ name ] = member;
    return (*this);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_string_vector_member( const key_string_type& name,
                                                           string_vector_member member )
  {
    m_string_vector_members[ name ] = member;
    return (*this);
  }

  //--------------------------------------------------------------------------
  // Overloaded Member Loaders
  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             bool_member member )
  {
    return add_bool_member(name,member);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             int_member member )
  {
    return add_int_member(name,member);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             float_member member )
  {
    return add_float_member(name,member);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             string_member member )
  {
    return add_string_member(name,member);
  }

  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             bool_vector_member member )
  {
    return add_bool_vector_member(name,member);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             int_vector_member member )
  {
    return add_int_vector_member(name,member);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             float_vector_member member )
  {
    return add_float_vector_member(name,member);
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  inline typename DataTranslator<T,B,I,F,S,K>::this_type&
    DataTranslator<T,B,I,F,S,K>::add_member( const key_string_type& name,
                                             string_vector_member member )
  {
    return add_string_vector_member(name,member);
  }

  //--------------------------------------------------------------------------
  // Overloaded Member Loaders
  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  template<typename Translator>
  inline typename DataTranslator<T,B,I,F,S,K>::size_type
    DataTranslator<T,B,I,F,S,K>::translate( value_type* object,
                                            const Translator& data )
    const
  {
    size_type count = 0;

    count += translate_scalar_data(object,data);
    count += translate_array_data(object,data);
    count += translate_vector_data(object,data);

    return count;
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  template<typename Translator>
  inline typename DataTranslator<T,B,I,F,S,K>::size_type
    DataTranslator<T,B,I,F,S,K>::translate_uniform( value_type* objects,
                                                    size_type size,
                                                    const Translator& data )
    const
  {
    if(size==0) return 0;

    // Translate the first object
    size_type result = translate( &objects[0], data );

    // Since objects are guaranteed to be linearly arranged, memcpy all after
    // the first one is created.
    if(size > 1 )
    {
      std::memcpy( &objects[1], &objects[0], (size - 1) * sizeof(value_type) );
    }
    return result;

  }

  //--------------------------------------------------------------------------
  // Translate Members
  //--------------------------------------------------------------------------

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  template<typename Translator>
  inline typename DataTranslator<T,B,I,F,S,K>::size_type
    DataTranslator<T,B,I,F,S,K>::translate_scalar_data( value_type* object,
                                                        const Translator& data )
    const
  {
    size_type count = 0;

    for( auto const& pair : m_bool_members )
    {
      const bool_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        (*object).*ptr = data.as_bool(pair.first);
      }
    }

    for( auto const& pair : m_int_members )
    {
      const int_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        (*object).*ptr = data.as_int(pair.first);
      }
    }

    for( auto const& pair : m_float_members )
    {
      const float_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        (*object).*ptr = data.as_float(pair.first);
      }
    }

    for( auto const& pair : m_string_members )
    {
      const string_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        (*object).*ptr = data.as_string(pair.first);
      }
    }
    return count;
  }

  template<typename T, typename B, typename I, typename F, typename S, typename K>
  template<typename Translator>
  inline typename DataTranslator<T,B,I,F,S,K>::size_type
    DataTranslator<T,B,I,F,S,K>::translate_vector_data( value_type* object,
                                                        const Translator& data )
    const
  {
    size_type count = 0;

    for( auto const& pair : m_bool_vector_members )
    {
      const bool_vector_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        data.template as_bool_sequence(pair.first, [&](const bool_type& value){
          ((*object).*ptr).push_back(value);
        });
      }
    }

    for( auto const& pair : m_int_vector_members )
    {
      const int_vector_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        data.template as_int_sequence(pair.first, [&](const int_type& value){
          ((*object).*ptr).push_back(value);
        });
      }
    }

    for( auto const& pair : m_float_vector_members )
    {
      const float_vector_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        data.template as_float_sequence(pair.first, [&](const float_type& value){
          ((*object).*ptr).push_back(value);
        });
      }
    }

    for( auto const& pair : m_string_vector_members )
    {
      const string_vector_member ptr = pair.second;

      if(data.has(pair.first))
      {
        ++count;
        data.template as_string_sequence(pair.first, [&](const string_type& value){
          ((*object).*ptr).push_back(value);
        });
      }
    }
    return count;
  }

} // namespace serial

#endif /* DETAIL_DATATRANSLATOR_INL_ */
