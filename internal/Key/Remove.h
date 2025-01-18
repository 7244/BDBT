#if defined(BDBT_set_MaxKeySize)
  _BDBT_P(Remove_InternalDataPerKeyNode_t) idpkn[BDBT_set_MaxKeySize / BDBT_set_BitPerNode];
#endif

uint8_t *kp8 = (uint8_t *)Key;
if(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[KeySize / 8 - 1];
}
else{
  kp8 = (uint8_t *)Key;
}

_BDBT_P(KeySize_t) From = 0;
{
  _BDBT_P(KeySize_t) KeyIndex = 0;
  while(KeyIndex != KeySize / BDBT_set_BitPerNode){
    uint8_t Byte = *kp8;
    if(BitOrderMatters == true){
      Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
    }
    for(uint8_t i = 0; i < 8 / BDBT_set_BitPerNode; i++){
      uint8_t k = Byte & _BDBT_ElementPerNode - 1;
      idpkn[KeyIndex + i].tna = *cnr;
      idpkn[KeyIndex + i].tka = k;
      _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, *cnr);
      *cnr = Node->n[k];
      for(_BDBT_bip(_neit_t) ki = 0; ki < _BDBT_ElementPerNode; ki++){
        if(ki == k){
          continue;
        }
        if(!_BDBT_bfcall(inric, Node->n[ki])){
          From = KeyIndex + i;
          break;
        }
      }
      Byte >>= BDBT_set_BitPerNode;
    }
    KeyIndex += 8 / BDBT_set_BitPerNode;
    if(BitOrderMatters == true && ENDIAN == 1){
      kp8--;
    }
    else{
      kp8++;
    }
  }
}

{
  _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, idpkn[From].tna);
  Node->n[idpkn[From].tka] = _BDBT_bfcall(gnric);
  ++From;
}

for(_BDBT_P(KeySize_t) i = From; i < KeySize / BDBT_set_BitPerNode; i++){
  _BDBT_bfcall(Recycle, idpkn[i].tna);
}

return From * BDBT_set_BitPerNode;
