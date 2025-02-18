#ifdef BDBT_set_declare_basic_types
  #error outdated setting. now it shipped with BDBT_set_declare_rest
#endif
#ifdef BDBT_set_Language
  #error outdated setting. define BDBT_set_lc or BDBT_set_lcpp instead.
#endif
#ifdef BDBT_set_BaseLibrary
  #error outdated setting. this is no longer here.
#endif
#ifdef BDBT_set_IsNodeUnlinked
  #error outdated setting BDBT_set_IsNodeUnlinked. this is no longer supported.
#endif
#ifdef BDBT_set_UseUninitialisedValues
  #error outdated setting BDBT_set_UseUninitialisedValues. __sanit is used instead.
#endif
#ifdef BDBT_set_namespace
  #error outdated setting BDBT_set_namespace. use namespace keyword instead.
#endif
#ifdef BDBT_set_base_namespace
  #error outdated setting BDBT_set_base_namespace. use namespace keyword instead.
#endif

#ifdef BDBT_set_alloc_open
  #error outdated setting. now its handled by bcontainer.
#endif
#ifdef BDBT_set_alloc_resize
  #error outdated setting. now its handled by bcontainer.
#endif
#ifdef BDBT_set_alloc_close
  #error outdated setting. now its handled by bcontainer.
#endif

#ifdef BDBT_set_StoreFormat
  #error outdated setting. now its handled by bcontainer.
#endif
#ifdef BDBT_set_RuntimePreallocate
  #error outdated setting. now its handled by bcontainer.
#endif
#ifdef BDBT_set_PreserveSome
  #error outdated setting. now its handled by bcontainer.
#endif
