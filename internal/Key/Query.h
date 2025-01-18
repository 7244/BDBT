uint8_t *kp8;
if(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[KeySize / 8 - 1];
}
else{
  kp8 = (uint8_t *)Key;
}
*KeyIndex = 0;
while(*KeyIndex != KeySize){
  uint8_t Byte = *kp8;
  if(BitOrderMatters == true){
    Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
  }
  for(uint8_t i = 0; i < 8; i += BDBT_set_BitPerNode){
    uint8_t k = Byte & _BDBT_ElementPerNode - 1;
    _BDBT_BP(NodeReference_t) nnr = _BDBT_bfcall(GetNodeByReference, *cnr)->n[k];
    if(_BDBT_bfcall(inric, nnr)){
      *KeyIndex += i;
      return;
    }
    *cnr = nnr;
    Byte >>= BDBT_set_BitPerNode;
  }
  *KeyIndex += 8;
  if(BitOrderMatters == true && ENDIAN == 1){
    kp8--;
  }
  else{
    kp8++;
  }
}
