uint8_t *kp8;
if(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[_BDBT_KeySize / 8 - 1];
}
else{
  kp8 = (uint8_t *)Key;
}
_BDBT_P(KeySize_t) KeyIndex = 0;
while(KeyIndex != _BDBT_KeySize){
  uint8_t Byte = *kp8;
  if(BitOrderMatters == true){
    Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
  }
  for(uint8_t i = 0; i < 8; i += BDBT_set_BitPerNode){
    uint8_t k = Byte & _BDBT_ElementPerNode - 1;
    _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, *cnr);
    *cnr = Node->n[k];
    Byte >>= BDBT_set_BitPerNode;
  }
  KeyIndex += 8;
  if(BitOrderMatters == true && ENDIAN == 1){
    kp8--;
  }
  else{
    kp8++;
  }
}
