typedef BDBT_set_type_node _BDBT_P(NodeReference_t);

/* node element iterator */
#if _BDBT_ElementPerNode <= 0xff
  typedef uint8_t _BDBT_P(_neit_t);
#elif _BDBT_ElementPerNode <= 0xffff
  typedef uint16_t _BDBT_P(_neit_t);
#else
  #error no
#endif

#if BDBT_set_MultiThread
  #define BME_set_Prefix _BDBT_BP(_FastLock)
  #define BME_set_LockValue 1
  #define BME_set_Sleep 0
  #define BME_set_CountLockFail BDBT_set_CountLockFail
  #ifdef BDBT_set_CountLockFailGlobal
    #define BME_set_CountLockFailGlobal BDBT_set_CountLockFailGlobal
  #endif
  #include <BME/BME.h>
#endif

#if BDBT_set_PadNode == 0
  #pragma pack(push, 1)
#endif
  BDBT_StructBegin(_BDBT_P(Node_t))
    _BDBT_P(NodeReference_t) n[_BDBT_ElementPerNode];
    #if BDBT_set_MultiThread
      _BDBT_BP(_FastLock_t) locks[_BDBT_ElementPerNode];
    #endif
  BDBT_StructEnd(_BDBT_P(Node_t))
#if BDBT_set_PadNode == 0
  #pragma pack(pop)
#endif

#define bcontainer_set_Prefix _BDBT_P(_NodeList)
#if BDBT_set_PointerNodeID
  #define bcontainer_set_PointerNodeType BDBT_set_PointerNodeID
#else
  #define bcontainer_set_NodeType BDBT_set_type_node
#endif
#define bcontainer_set_NodeData _BDBT_P(Node_t)
#define bcontainer_set_Recycle BDBT_set_Recycle
#define bcontainer_set_MultiThread BDBT_set_MultiThread
#define bcontainer_set_CountLockFail BDBT_set_CountLockFail
#ifdef BDBT_set_CountLockFailGlobal
  #define bcontainer_set_CountLockFailGlobal BDBT_set_CountLockFailGlobal
#endif
#include <bcontainer/bcontainer.h>

static uint8_t _BDBT_P(_ReverseKeyByte)(
  uint8_t p
){
  #if BDBT_set_BitPerNode == 1
    p = (p & 0xf0) >> 4 | (p & 0x0f) << 4;
    p = (p & 0xcc) >> 2 | (p & 0x33) << 2;
    p = (p & 0xaa) >> 1 | (p & 0x55) << 1;
  #elif BDBT_set_BitPerNode == 2
    p = (p & 0xf0) >> 4 | (p & 0x0f) << 4;
    p = (p & 0xcc) >> 2 | (p & 0x33) << 2;
  #elif BDBT_set_BitPerNode == 4
    p = (p & 0xf0) >> 4 | (p & 0x0f) << 4;
  #elif BDBT_set_BitPerNode == 8
    /* ~cheesecake~ */
  #else
    #error ?
  #endif

  return p;
}

BDBT_StructBegin(_BDBT_P(t))
  _BDBT_P(_NodeList_t) NodeList;

#ifdef BDBT_set_lc
  BDBT_StructEnd(_BDBT_P(t))
#endif

  /* get node reference invalid constant */
  _BDBT_fdec(_BDBT_P(NodeReference_t), gnric
  ){
    return (_BDBT_P(NodeReference_t))-1;
  }

  /* is node reference invalid constant */
  _BDBT_fdec(bool, inric,
    _BDBT_P(NodeReference_t) NodeReference
  ){
    return NodeReference == _BDBT_fcall(gnric);
  }

  _BDBT_fdec(_BDBT_P(Node_t) *, GetNodeByReference,
    _BDBT_P(NodeReference_t) node_id
  ){
    return _BDBT_P(_NodeList_GetNode)(&_BDBT_this->NodeList, node_id);
  }

  __forceinline
  _BDBT_fdec(_BDBT_P(NodeReference_t), Usage
  ){
    return _BDBT_P(_NodeList_Usage)(&_BDBT_this->NodeList);
  }

  _BDBT_fdec(__forceinline _BDBT_P(NodeReference_t), WhatRootWouldBe
  ){
    return _BDBT_P(_NodeList_WhatFirstWouldBe)(&_BDBT_this->NodeList);
  }

  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode
  ){
    _BDBT_P(NodeReference_t) node_id = _BDBT_P(_NodeList_NewNode)(&_BDBT_this->NodeList);

    _BDBT_P(Node_t) *Node = _BDBT_fcall(GetNodeByReference, node_id);
    for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
      Node->n[i] = _BDBT_fcall(gnric);
      #if BDBT_set_MultiThread
        _BDBT_BP(_FastLock_Init)(&Node->locks[i]);
      #endif
    }

    return node_id;
  }
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNodeBranchly,
    _BDBT_P(NodeReference_t) *BNR /* branch node references */
  ){
    _BDBT_P(NodeReference_t) node_id = _BDBT_P(_NodeList_NewNode)(&_BDBT_this->NodeList);

    _BDBT_P(Node_t) *Node = _BDBT_fcall(GetNodeByReference, node_id);
    for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
      Node->n[i] = BNR[i];
      #if BDBT_set_MultiThread
        _BDBT_BP(_FastLock_Init)(&Node->locks[i]);
      #endif
    }

    return node_id;
  }

  #if BDBT_set_Recycle
    _BDBT_fdec(__forceinline void, Recycle,
      _BDBT_P(NodeReference_t) node_id
    ){
      _BDBT_P(_NodeList_Recycle)(&_BDBT_this->NodeList, node_id);
    }
  #endif

  /* is node reference has child */
  _BDBT_fdec(bool, inrhc,
    _BDBT_P(NodeReference_t) nr
  ){
    _BDBT_P(Node_t) *n = _BDBT_fcall(GetNodeByReference, nr);
    for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
      if(!_BDBT_fcall(inric, n->n[i])){
        return 1;
      }
    }
    return 0;
  }

  _BDBT_fdec(void, Open
  ){
    _BDBT_P(_NodeList_Open)(&_BDBT_this->NodeList);
  }
  _BDBT_fdec(void, Close
  ){
    _BDBT_P(_NodeList_Close)(&_BDBT_this->NodeList);
  }
  _BDBT_fdec(void, Clear
  ){
    _BDBT_P(_NodeList_Clear)(&_BDBT_this->NodeList);
  }

  #ifdef BDBT_set_CPP_ConstructDestruct
    _BDBT_P(t)(){
      _BDBT_fcall(Open);
    }
    ~_BDBT_P(t)(){
      _BDBT_fcall(Close);
    }
  #endif

#ifdef BDBT_set_lcpp
  BDBT_StructEnd(_BDBT_P(t))
#endif
