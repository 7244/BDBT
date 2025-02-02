gt_begin:

_BDBT_P(Traverse_InternalDataPerKeyNode_t) *idkn = &idpkn[tra->Current];

while(
  BitOrder == _BDBT_P(BitOrderHigh) ?
  idkn->k != (_BDBT_BP(_neit_t))-1 :
  idkn->k < _BDBT_ElementPerNode
){
  _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, idkn->n);

  _BDBT_BP(_neit_t) tk = idkn->k;
  BitOrder == _BDBT_P(BitOrderHigh) ? --idkn->k : ++idkn->k;

  _BDBT_BP(NodeReference_t) nnr = Node->n[tk];
  if(_BDBT_bfcall(inric, nnr)){
    continue;
  }

  _BDBT_P(KeySize_t) d8;
  _BDBT_P(KeySize_t) m8;
  if(BitOrderMatters == true){
    d8 = (_BDBT_KeySize / 8 - 1) - (tra->Current * BDBT_set_BitPerNode / 8);
    m8 = (8 - BDBT_set_BitPerNode) - tra->Current * BDBT_set_BitPerNode % 8;
  }
  else{
    d8 = tra->Current * BDBT_set_BitPerNode / 8;
    m8 = tra->Current * BDBT_set_BitPerNode % 8;
  }

  #if __sanit
    if(BitOrderMatters == true){
      if(m8 == 8 - BDBT_set_BitPerNode){
        ((uint8_t *)Key)[d8] = 0;
      }
    }
    else{
      if(m8 == 0){
        ((uint8_t *)Key)[d8] = 0;
      }
    }
  #endif

  ((uint8_t *)Key)[d8] ^= ((uint8_t *)Key)[d8] & _BDBT_ElementPerNode - 1 << m8;
  ((uint8_t *)Key)[d8] |= tk << m8;

  if(tra->Current == _BDBT_KeySize / BDBT_set_BitPerNode - 1){
    tra->Output = nnr;
    return 1;
  }

  idkn = &idpkn[++tra->Current];
  idkn->n = nnr;
  idkn->k = BitOrder == _BDBT_P(BitOrderHigh) ? _BDBT_ElementPerNode - 1 : 0;
}
if(tra->Current == 0){
  return 0;
}
--tra->Current;
goto gt_begin;
