#include "internal/CheckObsolete.h"

#if !defined(BDBT_set_lc) && !defined(BDBT_set_lcpp)
  #if defined(__language_c) && !defined(__language_cpp)
    #define BDBT_set_lc
  #else
    #error BDBT_set_lc or BDBT_set_lcpp needs to be defined
  #endif
#endif

#if defined(BDBT_set_KeySize) && defined(BDBT_set_MaxKeySize)
  #error dont define BDBT_set_MaxKeySize if you define BDBT_set_KeySize
#endif

#ifndef BDBT_set_AreWeInsideStruct
  #define BDBT_set_AreWeInsideStruct 0
#endif

#ifndef BDBT_set_prefix
  #error ifndef BDBT_set_prefix
#endif
#ifndef BDBT_set_base_prefix
  #define BDBT_set_base_prefix BDBT_set_prefix
#endif
#ifndef BDBT_set_StructFormat
  #if defined(BDBT_set_lc)
    #define BDBT_set_StructFormat 0
  #elif defined(BDBT_set_lcpp)
    #define BDBT_set_StructFormat 1
  #else
    #error ?
  #endif
#endif
#ifndef BDBT_set_declare_rest
  #define BDBT_set_declare_rest 1
#endif
#ifndef BDBT_set_declare_Key
  #define BDBT_set_declare_Key 1
#endif
#ifndef BDBT_set_Recycle
  #define BDBT_set_Recycle 1
#endif
#ifndef BDBT_set_UseZeroAsInvalid
  #define BDBT_set_UseZeroAsInvalid 0
#endif
#ifndef BDBT_set_PadNode
  #define BDBT_set_PadNode 0
#endif
#ifndef BDBT_set_ResizeListAfterClear
  #define BDBT_set_ResizeListAfterClear 0
#endif
#ifndef BDBT_set_PointerNodeID
  #define BDBT_set_PointerNodeID 0
#endif
#ifndef BDBT_set_type_node
  #if BDBT_set_PointerNodeID
    #define BDBT_set_type_node uintptr_t
  #else
    #define BDBT_set_type_node uint32_t
  #endif
#else
  #if BDBT_set_PointerNodeID
    #error dont define BDBT_set_type_node
  #endif
#endif
#ifndef BDBT_set_BitPerNode
  #define BDBT_set_BitPerNode 2
#endif
#ifndef BDBT_set_Clear
  #define BDBT_set_Clear 0
#endif
#ifndef BDBT_set_MultiThread
  #define BDBT_set_MultiThread 0
#endif
#ifndef BDBT_set_CountLockFail
  #define BDBT_set_CountLockFail 0
#endif

#ifndef BDBT_set_RuntimePreallocate
  #if !BDBT_set_MultiThread
    #define BDBT_set_RuntimePreallocate 0
  #else
    #define BDBT_set_RuntimePreallocate 1
  #endif
#endif

#define _BDBT_BP(p0) CONCAT3(BDBT_set_base_prefix, _, p0)
#define _BDBT_P(p0) CONCAT3(BDBT_set_prefix, _, p0)

#include "internal/PrepareAndInclude.h"

#undef _BDBT_P
#undef _BDBT_BP

#ifdef BDBT_set_KeySize
  #undef BDBT_set_KeySize
#endif
#ifdef BDBT_set_MaxKeySize
  #undef BDBT_set_MaxKeySize
#endif

#undef BDBT_set_RuntimePreallocate
#undef BDBT_set_StoreFormat
#ifdef BDBT_set_CountLockFailGlobal
  #undef BDBT_set_CountLockFailGlobal
#endif
#undef BDBT_set_CountLockFail
#undef BDBT_set_MultiThread
#undef BDBT_set_Clear
#undef BDBT_set_BitPerNode
#ifdef BDBT_set_CPP_ConstructDestruct
  #undef BDBT_set_CPP_ConstructDestruct
#endif
#undef BDBT_set_base_prefix
#undef BDBT_set_prefix
#undef BDBT_set_declare_Key
#undef BDBT_set_declare_rest
#undef BDBT_set_type_node
#undef BDBT_set_PointerNodeID
#undef BDBT_set_UseZeroAsInvalid
#undef BDBT_set_Recycle
#undef BDBT_set_PadNode
#undef BDBT_set_ResizeListAfterClear

#ifdef BDBT_set_lc
  #undef BDBT_set_lc
#endif
#ifdef BDBT_set_lcpp
  #undef BDBT_set_lcpp
#endif
