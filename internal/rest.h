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

#if BDBT_set_StoreFormat == 1
  __forceinline static uint8_t _BDBT_P(_GetNodeListByNodeID)(
    _BDBT_P(NodeReference_t) node_id
  ){
    if(sizeof(_BDBT_P(NodeReference_t)) * 8 == 8){
      return __fast_8log2(node_id);
    }
    else if(sizeof(_BDBT_P(NodeReference_t)) * 8 == 16){
      return __fast_16log2(node_id);
    }
    else if(sizeof(_BDBT_P(NodeReference_t)) * 8 == 32){
      return __fast_32log2(node_id);
    }
    else if(sizeof(_BDBT_P(NodeReference_t)) * 8 == 64){
      return __fast_64log2(node_id);
    }
    else{
      __abort();
    }
  }
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

#define BVEC_set_prefix _BDBT_P(_NodeList)
#define BVEC_set_NodeType BDBT_set_type_node
#define BVEC_set_NodeData _BDBT_P(Node_t)
#include <BVEC/BVEC.h>

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
  #if BDBT_set_StoreFormat == 0
    _BDBT_P(_NodeList_t) NodeList;
  #elif BDBT_set_StoreFormat == 1
    _BDBT_BP(Node_t) *NodeLists[(uintptr_t)1 << __compile_time_log2(sizeof(_BDBT_P(NodeReference_t)) * 8)];
    BDBT_set_type_node Current;

    #if BDBT_set_MultiThread
      _BDBT_BP(_FastLock_t) NodeListsLocks[(uintptr_t)1 << __compile_time_log2(sizeof(_BDBT_P(NodeReference_t)) * 8)];
    #endif
  #else
    #error ?
  #endif

  #if BDBT_set_Recycle
    struct{
      _BDBT_P(NodeReference_t) c;
      _BDBT_P(NodeReference_t) p;
    }e;
  #endif

#ifdef BDBT_set_lc
  BDBT_StructEnd(_BDBT_P(t))
#endif

  /* is node reference invalid */
  _BDBT_fdec(bool, inri,
    _BDBT_P(NodeReference_t) node_id
  ){
    #if BDBT_set_StoreFormat == 0
      #if !BDBT_set_MultiThread
        return node_id >= _BDBT_this->NodeList.Current;
      #else
        #error not gonna be implemented
      #endif
    #elif BDBT_set_StoreFormat == 1
      #if !BDBT_set_MultiThread
        if(node_id >= __atomic_load_n(&_BDBT_this->Current, __ATOMIC_SEQ_CST)){
          return 1;
        }
        if(__atomic_load_n(&_BDBT_this->NodeLists[_BDBT_P(_GetNodeListByNodeID)(node_id)], __ATOMIC_SEQ_CST) == NULL){
          return 1;
        }
        return 0;
      #else
        if(node_id >= _BDBT_this->Current){
          return 1;
        }
        if(_BDBT_this->NodeLists[_BDBT_P(_GetNodeListByNodeID)(node_id)] == NULL){
          return 1;
        }
        return 0;
      #endif
    #else
      #error ?
    #endif
  }

  /* get node reference invalid constant */
  _BDBT_fdec(_BDBT_P(NodeReference_t), gnric
  ){
    return (_BDBT_P(NodeReference_t))
      #if BDBT_set_UseZeroAsInvalid == 0
        -1
      #else
        0
      #endif
    ;
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
    #if BDBT_set_StoreFormat == 0
      return &((_BDBT_P(Node_t) *)&_BDBT_this->NodeList.ptr[0])[node_id];
    #elif BDBT_set_StoreFormat == 1
      uint8_t NodeList = _BDBT_P(_GetNodeListByNodeID)(node_id);
      node_id -= (_BDBT_P(NodeReference_t))1 << NodeList;
      return &_BDBT_this->NodeLists[NodeList][node_id];
    #else
      #error ?
    #endif
  }

  _BDBT_fdec(_BDBT_P(NodeReference_t), usage
  ){
    return
      #if BDBT_set_StoreFormat == 0
        _BDBT_this->NodeList.Current
      #elif BDBT_set_StoreFormat == 1
        _BDBT_this->Current
      #else
        #error ?
      #endif
      #if BDBT_set_Recycle
        - _BDBT_this->e.p
      #endif
    ;
  }

  _BDBT_fdec(__forceinline _BDBT_P(NodeReference_t), WhatRootWouldBe
  ){
    #if BDBT_set_StoreFormat == 0
      return 0;
    #elif BDBT_set_StoreFormat == 1
      return 1;
    #else
      #error ?
    #endif
  }

  #if BDBT_set_Recycle
    _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode_empty
    ){
      #if BDBT_set_MultiThread
        #error not implemented
      #endif
      _BDBT_P(NodeReference_t) NodeReference = _BDBT_this->e.c;
      _BDBT_this->e.c = _BDBT_fcall(GetNodeByReference, NodeReference)->n[0];
      _BDBT_this->e.p--;
      return NodeReference;
    }
  #endif
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode_alloc
  ){
    #if BDBT_set_StoreFormat == 0
      #if BDBT_set_MultiThread
        #error not gonna be implemented
      #endif

      _BDBT_P(_NodeList_AddEmpty)(&_BDBT_this->NodeList, 1);

      BDBT_set_type_node ret = _BDBT_this->NodeList.Current - 1;

      return ret;
    #elif BDBT_set_StoreFormat == 1
      #if !BDBT_set_MultiThread
        BDBT_set_type_node node_id = _BDBT_this->Current++;
        uint8_t NodeList = _BDBT_P(_GetNodeListByNodeID)(node_id);
        if(_BDBT_this->NodeLists[NodeList] == NULL){
          _BDBT_this->NodeLists[NodeList] =
            (_BDBT_P(Node_t) *)BDBT_set_alloc_open(((uintptr_t)1 << NodeList) * sizeof(_BDBT_P(Node_t)));
        }
        return node_id;
      #else
        BDBT_set_type_node node_id = __atomic_fetch_add(&_BDBT_this->Current, 1, __ATOMIC_SEQ_CST);
        uint8_t NodeList = _BDBT_P(_GetNodeListByNodeID)(node_id);
        if(__atomic_load_n(&_BDBT_this->NodeLists[NodeList], __ATOMIC_RELAXED) == NULL){
          while(_BDBT_P(_FastLock_Lock)(&_BDBT_this->NodeListsLocks[NodeList])){ /* TOOD cpu relax */ }
          if(__atomic_load_n(&_BDBT_this->NodeLists[NodeList], __ATOMIC_SEQ_CST) == NULL){
            __atomic_exchange_n(
              &_BDBT_this->NodeLists[NodeList],
              BDBT_set_alloc_open(((uintptr_t)1 << NodeList) * sizeof(_BDBT_P(Node_t))),
              __ATOMIC_SEQ_CST
            );
          }
          _BDBT_P(_FastLock_Unlock)(&_BDBT_this->NodeListsLocks[NodeList]);
        }
        return node_id;
      #endif
    #else
      #error ?
    #endif
  }
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode
  ){
    _BDBT_P(NodeReference_t) NodeReference;
    if(0);
    #if BDBT_set_Recycle
      else if(_BDBT_this->e.p){
        NodeReference = _BDBT_fcall(NewNode_empty);
      }
    #endif
    else{
      NodeReference = _BDBT_fcall(NewNode_alloc);
    }

    {
      _BDBT_P(Node_t) *Node = _BDBT_fcall(GetNodeByReference, NodeReference);
      for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
        Node->n[i] = _BDBT_fcall(gnric);
        #if BDBT_set_MultiThread
          _BDBT_BP(_FastLock_Init)(&Node->locks[i]);
        #endif
      }
    }

    return NodeReference;
  }
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNodeBranchly,
    _BDBT_P(NodeReference_t) *BNR /* branch node references */
  ){
    _BDBT_P(NodeReference_t) NodeReference;
    if(0);
    #if BDBT_set_Recycle
      else if(_BDBT_this->e.p){
        NodeReference = _BDBT_fcall(NewNode_empty);
      }
    #endif
    else{
      NodeReference = _BDBT_fcall(NewNode_alloc);
    }

    {
      _BDBT_P(Node_t) *Node = _BDBT_fcall(GetNodeByReference, NodeReference);
      for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
        Node->n[i] = BNR[i];
        #if BDBT_set_MultiThread
          _BDBT_BP(_FastLock_Init)(&Node->locks[i]);
        #endif
      }
    }

    return NodeReference;
  }

  #if BDBT_set_Recycle
    _BDBT_fdec(void, Recycle,
      _BDBT_P(NodeReference_t) NodeReference
    ){
      _BDBT_P(Node_t) *Node = _BDBT_fcall(GetNodeByReference, NodeReference);

      Node->n[0] = _BDBT_this->e.c;
      _BDBT_this->e.c = NodeReference;
      _BDBT_this->e.p++;
    }
  #endif

  #if BDBT_set_StoreFormat == 0
    _BDBT_fdec(void, PreAllocateNodes,
      _BDBT_P(NodeReference_t) Amount
    ){
      _BDBT_P(_NodeList_Reserve)(&_BDBT_this->NodeList, Amount);
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

  _BDBT_fdec(void, _AfterInitNodes
  ){
    #if BDBT_set_Recycle
      _BDBT_this->e.p = 0;
    #endif

    #if BDBT_set_UseZeroAsInvalid == 1
      /* first is reserved */

      #if BDBT_set_StoreFormat == 0
        _BDBT_P(_NodeList_AddEmpty)(&_BDBT_this->NodeList, 1);
      #elif BDBT_set_StoreFormat == 1
        #error implement this
      #else
        #error ?
      #endif
    #endif
  }

  _BDBT_fdec(void, Open
  ){
    #if __sanit
      _BDBT_this->e.c = 0;
    #endif

    #if BDBT_set_StoreFormat == 0
      _BDBT_P(_NodeList_Open)(&_BDBT_this->NodeList);
    #elif BDBT_set_StoreFormat == 1
      _BDBT_this->Current = _BDBT_fcall(WhatRootWouldBe);

      for(
        uintptr_t i = (uintptr_t)1 << __compile_time_log2(sizeof(_BDBT_P(NodeReference_t)) * 8);
        i--;
      ){
        _BDBT_this->NodeLists[i] = NULL;

        #if BDBT_set_MultiThread
          _BDBT_P(_FastLock_Init)(&_BDBT_this->NodeListsLocks[i]);
        #endif
      }
    #else
      #error ?
    #endif

    _BDBT_fcall(_AfterInitNodes);
  }
  _BDBT_fdec(void, Close
  ){
    #if BDBT_set_StoreFormat == 0
      _BDBT_P(_NodeList_Close)(&_BDBT_this->NodeList);
    #elif BDBT_set_StoreFormat == 1
      for(
        uintptr_t i = (uintptr_t)1 << __compile_time_log2(sizeof(_BDBT_P(NodeReference_t)) * 8);
        i--;
      ){
        BDBT_set_alloc_close(_BDBT_this->NodeLists[i]);
      }
    #else
      #error ?
    #endif
  }
  _BDBT_fdec(void, Clear
  ){
    #if BDBT_set_StoreFormat == 0
      #if BDBT_set_ResizeListAfterClear == 1
        #error implement this
      #else
        _BDBT_P(_NodeList_Clear)(&_BDBT_this->NodeList);
      #endif
    #elif BDBT_set_StoreFormat == 1
      #if BDBT_set_ResizeListAfterClear == 1
        #error implement this
      #else
        _BDBT_this->Current = _BDBT_fcall(WhatRootWouldBe);
      #endif
    #else
      #error ?
    #endif

    _BDBT_fcall(_AfterInitNodes);
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
