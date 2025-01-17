uint8_t *kp8;
if constexpr(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[KeySize / 8 - 1];
}
else{
  kp8 = (uint8_t *)Key;
}
*KeyIndex = 0;
while(*KeyIndex != KeySize){
  auto Byte = *kp8;
  if constexpr(BitOrderMatters == true){
    Byte = list->_ReverseKeyByte(Byte);
  }
  for(uint8_t i = 0; i < 8; i += BDBT_set_BitPerNode){
    auto k = Byte & _BDBT_ElementPerNode - 1;
    auto nnr = list->GetNodeByReference(*cnr)->n[k];
    if(list->inric(nnr)){
      *KeyIndex += i;
      return;
    }
    *cnr = nnr;
    Byte >>= BDBT_set_BitPerNode;
  }
  *KeyIndex += 8;
  if constexpr(BitOrderMatters == true && ENDIAN == 1){
    kp8--;
  }
  else{
    kp8++;
  }
}
