typedef uint8_t _BDBT_P(BitOrder_t);
const static _BDBT_P(BitOrder_t) _BDBT_P(BitOrderLow) = 0;
const static _BDBT_P(BitOrder_t) _BDBT_P(BitOrderHigh) = 1;
const static _BDBT_P(BitOrder_t) _BDBT_P(BitOrderAny) = 2;

typedef uintptr_t _BDBT_P(KeySize_t);

static void _BDBT_P(Add)(
  _BDBT_BP(t) *tree,
  bool BitOrderMatters,
  _BDBT_P(KeySize_t) KeySize,
  const void *Key,
  _BDBT_P(KeySize_t) KeyIndex,
  _BDBT_BP(NodeReference_t) cnr,
  _BDBT_BP(NodeReference_t) Output
){
  #include "Add.h"
}

static void _BDBT_P(Query)(
  _BDBT_BP(t) *tree,
  bool BitOrderMatters,
  _BDBT_P(KeySize_t) KeySize,
  const void *Key,
  _BDBT_P(KeySize_t) *KeyIndex,
  _BDBT_BP(NodeReference_t) **cnr
){
  #include "Query.h"
}

static void _BDBT_P(QueryNoPointer)(
  _BDBT_BP(t) *tree,
  bool BitOrderMatters,
  _BDBT_P(KeySize_t) KeySize,
  const void *Key,
  _BDBT_P(KeySize_t) *KeyIndex,
  _BDBT_BP(NodeReference_t) *cnr
){
  _BDBT_BP(NodeReference_t) *rnr = cnr;
  _BDBT_P(Query)(
    tree,
    BitOrderMatters,
    KeySize,
    Key,
    KeyIndex,
    &rnr
  );
  *cnr = *rnr;
}

static void _BDBT_P(ConfidentQuery)(
  _BDBT_BP(t) *tree,
  bool BitOrderMatters,
  _BDBT_P(KeySize_t) KeySize,
  const void *Key,
  _BDBT_BP(NodeReference_t) *cnr
){
  #include "ConfidentQuery.h"
}

typedef struct{
  _BDBT_BP(NodeReference_t) tna;
  uint8_t tka;
}_BDBT_P(Remove_InternalDataPerKeyNode_t);

static _BDBT_P(KeySize_t) _BDBT_P(Remove)(
  _BDBT_BP(t) *tree,
  #if !defined(BDBT_set_MaxKeySize)
    _BDBT_P(Remove_InternalDataPerKeyNode_t) *idpkn,
  #endif
  bool BitOrderMatters,
  _BDBT_P(KeySize_t) KeySize,
  void *Key,
  _BDBT_BP(NodeReference_t) *cnr
){
  #include "Remove.h"
}

typedef struct{
  _BDBT_BP(NodeReference_t) n;
  _BDBT_bip(_neit_t) k;
}_BDBT_P(Traverse_InternalDataPerKeyNode_t);

typedef struct{
  _BDBT_P(KeySize_t) Current;
  _BDBT_BP(NodeReference_t) Output;

  #if defined(BDBT_set_MaxKeySize)
    _BDBT_P(Traverse_InternalDataPerKeyNode_t) idpkn[BDBT_set_MaxKeySize / BDBT_set_BitPerNode];
  #endif
}_BDBT_P(Traverse_t);

static void _BDBT_P(TraverseInit)(
  _BDBT_P(Traverse_t) *tra,
  _BDBT_P(BitOrder_t) BitOrder,
  #if !defined(BDBT_set_MaxKeySize)
    _BDBT_P(Traverse_InternalDataPerKeyNode_t) *idpkn,
  #endif
  _BDBT_BP(NodeReference_t) rnr
){
  tra->Current = 0;

  #if defined(BDBT_set_MaxKeySize)
    _BDBT_P(Traverse_InternalDataPerKeyNode_t) *idpkn = tra->idpkn;
  #endif

  idpkn[0].k = BitOrder == _BDBT_P(BitOrderHigh) ? _BDBT_ElementPerNode - 1 : 0;
  idpkn[0].n = rnr;
}

static bool _BDBT_P(Traverse)(
  _BDBT_BP(t) *tree,
  _BDBT_P(Traverse_t) *tra,
  #if !defined(BDBT_set_MaxKeySize)
    _BDBT_P(Traverse_InternalDataPerKeyNode_t) *idpkn,
  #endif
  bool BitOrderMatters,
  _BDBT_P(BitOrder_t) BitOrder,
  _BDBT_P(KeySize_t) KeySize,
  void *Key
){
  #if defined(BDBT_set_MaxKeySize)
    _BDBT_P(Traverse_InternalDataPerKeyNode_t) *idpkn = tra->idpkn;
  #endif

  #include "Traverse.h"
}
