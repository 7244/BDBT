gt_begin:
auto tp = &ta[Current];
while(
  BitOrder == BitOrderHigh ?
  tp->k != (_BDBT_bip(_neit_t))-1 :
  tp->k < _BDBT_ElementPerNode
){
  auto Node = list->GetNodeByReference(tp->n);

  _BDBT_bip(_neit_t) tk = tp->k;
  BitOrder == BitOrderHigh ? --tp->k : ++tp->k;

  _BDBT_BP(NodeReference_t) nnr = Node->n[tk];
  if(list->inric(nnr)){
    continue;
  }

  KeySize_t d8;
  KeySize_t m8;
  if constexpr(BitOrderMatters == true){
    d8 = (KeySize / 8 - 1) - (Current * BDBT_set_BitPerNode / 8);
    m8 = (8 - BDBT_set_BitPerNode) - Current * BDBT_set_BitPerNode % 8;
  }
  else{
    d8 = Current * BDBT_set_BitPerNode / 8;
    m8 = Current * BDBT_set_BitPerNode % 8;
  }

  #if __sanit
    if constexpr(BitOrderMatters == true){
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

  if(Current == KeySize / BDBT_set_BitPerNode - 1){
    Output = nnr;
    return 1;
  }

  tp = &ta[++Current];
  tp->n = nnr;
  tp->k = BitOrder == BitOrderHigh ? _BDBT_ElementPerNode - 1 : 0;
}
if(Current == 0){
  return 0;
}
--Current;
goto gt_begin;
