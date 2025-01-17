#define _BDBT_ElementPerNode (1 << BDBT_set_BitPerNode)

#if BDBT_set_StructFormat == 0
  #define BDBT_StructBegin(n) typedef struct{
  #define BDBT_StructEnd(n) }n;
#elif BDBT_set_StructFormat == 1
  #define BDBT_StructBegin(n) struct n{
  #define BDBT_StructEnd(n) };
#endif

#if defined(BDBT_set_lc)
  /* keyword prefix */
  #define _BDBT_ip(p) _BDBT_P(p)
  #define _BDBT_bip(p) _BDBT_BP(p)
  #define _BDBT_this This
  #define _BDBT_fdec(rtype, name, ...) static rtype name(_BDBT_P(t) *This, ##__VA_ARGS__)
  #define _BDBT_fcall(name, ...) name(This, ##__VA_ARGS__)
#elif defined(BDBT_set_lcpp)
  #define _BDBT_ip(p) p
  #define _BDBT_bip(p) CONCAT(BDBT_set_base_prefix,_t)::p
  #define _BDBT_this this
  #define _BDBT_fdec(rtype, name, ...) rtype name(__VA_ARGS__)
  #define _BDBT_fcall(name, ...) name(__VA_ARGS__)
#else
  #error ?
#endif

#if BDBT_set_declare_rest == 1
  #include "rest.h"
#endif
#if BDBT_set_declare_Key == 1
  #include "Key/Key.h"
#endif

/* identifier prefix */
/* base identifier prefix */
#undef _BDBT_ip
#undef _BDBT_bip
#undef _BDBT_this
#undef _BDBT_fdec
#undef _BDBT_fcall

#undef BDBT_StructBegin
#undef BDBT_StructEnd

#undef _BDBT_ElementPerNode
