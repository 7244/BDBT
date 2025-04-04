#define _BDBT_ElementPerNode (1 << BDBT_set_BitPerNode)

#if BDBT_set_StructFormat == 0
  #define BDBT_StructBegin(n) typedef struct{
  #define BDBT_StructEnd(n) }n;
#elif BDBT_set_StructFormat == 1
  #define BDBT_StructBegin(n) struct n{
  #define BDBT_StructEnd(n) };
#endif

#if defined(BDBT_set_lc)
  #define _BDBT_ip(p) _BDBT_P(p)
  #define _BDBT_bip(p) _BDBT_BP(p)
  #define _BDBT_this This
  #define _BDBT_fdec(rtype, name, ...) static rtype _BDBT_P(name)(_BDBT_P(t) *This, ##__VA_ARGS__)
  #define _BDBT_fcall(name, ...) _BDBT_P(name)(This, ##__VA_ARGS__)
  #define _BDBT_bfcall(name, ...) _BDBT_BP(name)(tree, ##__VA_ARGS__)
#elif defined(BDBT_set_lcpp)
  #define _BDBT_ip(p) p
  #define _BDBT_bip(p) CONCAT(BDBT_set_base_prefix,_t)::p
  #define _BDBT_this this
  #define _BDBT_fdec(rtype, name, ...) rtype name(__VA_ARGS__)
  #define _BDBT_fcall(name, ...) name(__VA_ARGS__)
  #define _BDBT_bfcall(name, ...) tree->name(__VA_ARGS__)
#else
  #error ?
#endif

#if BDBT_set_PointerNodeID
  #define _BDBT_WrappedID_t _BDBT_P(Node_t) *
#else
  #define _BDBT_WrappedID_t _BDBT_P(NodeReference_t)
#endif

#if BDBT_set_declare_rest == 1
  #include "rest.h"
#endif
#if BDBT_set_declare_Key == 1
  #if defined(BDBT_set_KeySize)
    #define _BDBT_KeySize (BDBT_set_KeySize)
  #endif
  #include "Key/Key.h"
  #if defined(BDBT_set_KeySize)
    #undef _BDBT_KeySize
  #endif
#endif

#undef _BDBT_WrappedID_t

/* ip == identifier prefix */
/* bip == base identifier prefix */

#undef _BDBT_ip
#undef _BDBT_bip
#undef _BDBT_this
#undef _BDBT_fdec
#undef _BDBT_fcall
#undef _BDBT_bfcall

#undef BDBT_StructBegin
#undef BDBT_StructEnd

#undef _BDBT_ElementPerNode
