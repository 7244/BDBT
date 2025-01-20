const uintptr_t BeforeLast = _BDBT_KeySize - 8;

uint8_t *kp8;
if(BitOrderMatters == true && ENDIAN == 1){
  kp8 = &((uint8_t *)Key)[_BDBT_KeySize / 8 - 1];
  kp8 -= KeyIndex / 8;
}
else{
  kp8 = (uint8_t *)Key;
  kp8 += KeyIndex / 8;
}

if(BeforeLast != 0){
  if(KeyIndex < BeforeLast){
    uint8_t m = KeyIndex % 8;
    uint8_t Byte = *kp8;
    if(BitOrderMatters == true){
      Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
    }
    Byte >>= m;
    for(uint8_t i = m; i < 8; i += BDBT_set_BitPerNode){
      uint8_t k = Byte & _BDBT_ElementPerNode - 1;
      _BDBT_BP(NodeReference_t) pnr = cnr;
      cnr = _BDBT_bfcall(NewNode);
      _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, pnr);
      Node->n[k] = cnr;
      Byte >>= BDBT_set_BitPerNode;
    }
    KeyIndex += 8 - m;
    if(BitOrderMatters == true && ENDIAN == 1){
      kp8--;
    }
    else{
      kp8++;
    }
  }
}
if(BeforeLast > 8){
  while(KeyIndex < BeforeLast){
    uint8_t Byte = *kp8;
    if(BitOrderMatters == true){
      Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
    }
    for(uint8_t i = 0; i < 8; i += BDBT_set_BitPerNode){
      uint8_t k = Byte & _BDBT_ElementPerNode - 1;
      _BDBT_BP(NodeReference_t) pnr = cnr;
      cnr = _BDBT_bfcall(NewNode);
      _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, pnr);
      Node->n[k] = cnr;
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
}
{
  uint8_t Byte = *kp8;
  if(BitOrderMatters == true){
    Byte = _BDBT_BP(_ReverseKeyByte)(Byte);
  }
  uint8_t m;
  if(BeforeLast == 0){
    m = KeyIndex;
  }
  else{
    m = KeyIndex % 8;
  }
  Byte >>= m;
  for(uint8_t i = 8 - BDBT_set_BitPerNode; i > m ; i -= BDBT_set_BitPerNode){
    uint8_t k = Byte & _BDBT_ElementPerNode - 1;
    _BDBT_BP(NodeReference_t) pnr = cnr;
    cnr = _BDBT_bfcall(NewNode);
    _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, pnr);
    Node->n[k] = cnr;
    Byte >>= BDBT_set_BitPerNode;
  }

  uint8_t k = Byte & _BDBT_ElementPerNode - 1;
  _BDBT_BP(Node_t) *Node = _BDBT_bfcall(GetNodeByReference, cnr);
  Node->n[k] = Output;
}
