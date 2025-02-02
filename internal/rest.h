typedef BDBT_set_type_node _BDBT_P(NodeReference_t);

/* node element iterator */
#if _BDBT_ElementPerNode <= 0xff
  typedef uint8_t _BDBT_P(_neit_t);
#elif _BDBT_ElementPerNode <= 0xffff
  typedef uint16_t _BDBT_P(_neit_t);
#else
  #error no
#endif

#if BDBT_set_PadNode == 0
  #pragma pack(push, 1)
#endif
  BDBT_StructBegin(_BDBT_P(Node_t))
    _BDBT_P(NodeReference_t) n[_BDBT_ElementPerNode];
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
  _BDBT_P(_NodeList_t) NodeList;
  struct{
    _BDBT_P(NodeReference_t) c;
    _BDBT_P(NodeReference_t) p;
  }e;

#ifdef BDBT_set_lc
  BDBT_StructEnd(_BDBT_P(t))
#endif

  /* is node reference invalid */
  _BDBT_fdec(bool, inri,
    _BDBT_P(NodeReference_t) NodeReference
  ){
    /* TODO it needs recycle check too */
    __abort();
    return NodeReference >= _BDBT_this->NodeList.Current;
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

  _BDBT_fdec(_BDBT_P(Node_t) *, _GetNodeByReference,
    _BDBT_P(NodeReference_t) NodeReference
  ){
    return &((_BDBT_P(Node_t) *)&_BDBT_this->NodeList.ptr[0])[NodeReference];
  }

  _BDBT_fdec(_BDBT_P(Node_t) *, GetNodeByReference,
    _BDBT_P(NodeReference_t) NodeReference
  ){
    #if BDBT_set_debug_InvalidAction == 1
      if(_BDBT_fcall(inri, NodeReference)){
        __abort();
      }
    #endif
    return _BDBT_fcall(_GetNodeByReference, NodeReference);
  }

  _BDBT_fdec(_BDBT_P(NodeReference_t), usage
  ){
    return _BDBT_this->NodeList.Current - _BDBT_this->e.p;
  }

  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode_empty
  ){
    _BDBT_P(NodeReference_t) NodeReference = _BDBT_this->e.c;
    _BDBT_this->e.c = _BDBT_fcall(_GetNodeByReference, NodeReference)->n[0];
    _BDBT_this->e.p--;
    return NodeReference;
  }
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode_alloc
  ){
    _BDBT_P(_NodeList_AddEmpty)(&_BDBT_this->NodeList, 1);
    return _BDBT_this->NodeList.Current - 1;
  }
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNode
  ){
    _BDBT_P(NodeReference_t) NodeReference;
    if(_BDBT_this->e.p){
      NodeReference = _BDBT_fcall(NewNode_empty);
    }
    else{
      NodeReference = _BDBT_fcall(NewNode_alloc);
    }

    {
      _BDBT_P(Node_t) *Node = _BDBT_fcall(_GetNodeByReference, NodeReference);
      for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
        Node->n[i] = _BDBT_fcall(gnric);
      }
    }

    return NodeReference;
  }
  _BDBT_fdec(_BDBT_P(NodeReference_t), NewNodeBranchly,
    _BDBT_P(NodeReference_t) *BNR /* branch node references */
  ){
    _BDBT_P(NodeReference_t) NodeReference;
    if(_BDBT_this->e.p){
      NodeReference = _BDBT_fcall(NewNode_empty);
    }
    else{
      NodeReference = _BDBT_fcall(NewNode_alloc);
    }

    {
      _BDBT_P(Node_t) *Node = _BDBT_fcall(_GetNodeByReference, NodeReference);
      for(_BDBT_P(_neit_t) i = 0; i < _BDBT_ElementPerNode; i++){
        Node->n[i] = BNR[i];
      }
    }

    return NodeReference;
  }

  _BDBT_fdec(void, Recycle,
    _BDBT_P(NodeReference_t) NodeReference
  ){
    _BDBT_P(Node_t) *Node = _BDBT_fcall(GetNodeByReference, NodeReference);

    Node->n[0] = _BDBT_this->e.c;
    _BDBT_this->e.c = NodeReference;
    _BDBT_this->e.p++;
  }

  _BDBT_fdec(void, PreAllocateNodes,
    _BDBT_P(NodeReference_t) Amount
  ){
    _BDBT_P(_NodeList_Reserve)(&_BDBT_this->NodeList, Amount);
  }

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
    _BDBT_this->e.p = 0;
    #if BDBT_set_UseZeroAsInvalid == 1
      /* reserved */
      _BDBT_P(_NodeList_AddEmpty)(&_BDBT_this->NodeList, 1);
    #endif
  }

  _BDBT_fdec(void, Open
  ){
    #if __sanit
      _BDBT_this->e.c = 0;
    #endif

    _BDBT_P(_NodeList_Open)(&_BDBT_this->NodeList);
    _BDBT_fcall(_AfterInitNodes);
  }
  _BDBT_fdec(void, Close
  ){
    _BDBT_P(_NodeList_Close)(&_BDBT_this->NodeList);
  }
  _BDBT_fdec(void, Clear
  ){
    #if BDBT_set_ResizeListAfterClear == 1
      /* TODO implement this */
      __abort();
    #else
      _BDBT_P(_NodeList_Clear)(&_BDBT_this->NodeList);
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
