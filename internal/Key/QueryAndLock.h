uint8_t *kp8;
if(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[_BDBT_KeySize / 8 - 1];
}
else{
  kp8 = (uint8_t *)Key;
}
*KeyIndex = 0;

uint8_t k;
_BDBT_BP(Node_t) *node;

while(*KeyIndex != _BDBT_KeySize){
  uint8_t Byte = *kp8;
  if(BitOrderMatters == true){
    Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
  }
  for(uint8_t i = 0; i < 8; i += BDBT_set_BitPerNode){
    k = Byte & _BDBT_ElementPerNode - 1;
    node = _BDBT_bfcall(GetNodeByReference, **cnr);
    if(_BDBT_bfcall(inric, __atomic_load_n(&node->n[k], __ATOMIC_RELAXED))){

      while(_BDBT_BP(_FastLock_Lock)(&node->locks[k])){ /* TOOD cpu relax */ }

      if(_BDBT_bfcall(inric, __atomic_load_n(&node->n[k], __ATOMIC_SEQ_CST))){
        *KeyIndex += i;
        return &node->locks[k];
      }

      _BDBT_BP(_FastLock_Unlock)(&node->locks[k]);
    }
    *cnr = &node->n[k];
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

while(_BDBT_BP(_FastLock_Lock)(&node->locks[k])){ /* TOOD cpu relax */ }
return &node->locks[k];
