uint8_t *kp8 = (uint8_t *)Key;
if constexpr(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[KeySize / 8 - 1];
}
else{
  kp8 = (uint8_t *)Key;
}

_BDBT_BP(NodeReference_t) tna[MaxKeySize / BDBT_set_BitPerNode];
uint8_t tka[MaxKeySize / BDBT_set_BitPerNode];

KeySize_t From = 0;
{
  KeySize_t KeyIndex = 0;
  while(KeyIndex != KeySize / BDBT_set_BitPerNode){
    uint8_t Byte = *kp8;
    if constexpr(BitOrderMatters == true){
      Byte = list->_ReverseKeyByte(Byte);
    }
    for(uint8_t i = 0; i < 8 / BDBT_set_BitPerNode; i++){
      uint8_t k = Byte & _BDBT_ElementPerNode - 1;
      tna[KeyIndex + i] = *cnr;
      tka[KeyIndex + i] = k;
      auto Node = list->GetNodeByReference(*cnr);
      *cnr = Node->n[k];
      for(_BDBT_BP(NodeEIT_t) ki = 0; ki < _BDBT_ElementPerNode; ki++){
        if(ki == k){
          continue;
        }
        if(!list->inric(Node->n[ki])){
          From = KeyIndex + i;
          break;
        }
      }
      Byte >>= BDBT_set_BitPerNode;
    }
    KeyIndex += 8 / BDBT_set_BitPerNode;
    if constexpr(BitOrderMatters == true && ENDIAN == 1){
      kp8--;
    }
    else{
      kp8++;
    }
  }
}

{
  auto Node = list->GetNodeByReference(tna[From]);
  Node->n[tka[From]] = list->gnric();
  ++From;
}

for(KeySize_t i = From; i < KeySize / BDBT_set_BitPerNode; i++){
  list->Recycle(tna[i]);
}

return From * BDBT_set_BitPerNode;
