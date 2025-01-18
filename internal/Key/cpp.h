#if !defined(BDBT_set_KeySize)
  template <uintptr_t _KeySize, bool BitOrderMatters = false>
#endif
struct _BDBT_P(Key_t){
  #if defined(BDBT_set_KeySize)
    /* TODO user need to spectify it in runtime. */
    constexpr static bool BitOrderMatters = true;
  #endif

  typedef uint8_t BitOrder_t;
  constexpr static BitOrder_t BitOrderLow = 0; /* low to high */
  constexpr static BitOrder_t BitOrderHigh = 1; /* high to low */
  constexpr static BitOrder_t BitOrderAny = 2; /* does not matter */

  #if !defined(BDBT_set_KeySize)
    typedef std::conditional_t<
      _KeySize <= 0xff,
      uint8_t,
        std::conditional_t<_KeySize <= 0xffff,
        uint16_t,
        uint32_t
      >
    >KeySize_t;
  #elif defined(BDBT_set_MaxKeySize)
    #if BDBT_set_MaxKeySize <= 0xff
      typedef uint8_t KeySize_t;
    #elif BDBT_set_MaxKeySize <= 0xffff
      typedef uint16_t KeySize_t;
    #elif BDBT_set_MaxKeySize <= 0xffffffff
      typedef uint32_t KeySize_t;
    #else
      #error ?
    #endif
  #else
    typedef uintptr_t KeySize_t;
  #endif

  #if !defined(BDBT_set_KeySize)
    constexpr static KeySize_t MaxKeySize = _KeySize;
  #elif defined(BDBT_set_MaxKeySize)
    constexpr static KeySize_t MaxKeySize = BDBT_set_MaxKeySize;
  #endif

  #if !defined(BDBT_set_KeySize)
    #define _BDBT_ksizeConstexpr constexpr

    #define KeySize (KeySize_t)_KeySize
  #else
    #define _BDBT_ksizeConstexpr

    #define KeySize KeySize
  #endif

  #define BeforeLast (KeySize - 8)

  /* add */
  static
  void
  a
  (
    _BDBT_BP(t) *list,
    #if defined(BDBT_set_KeySize)
      KeySize_t KeySize,
    #endif
    const void *Key,
    KeySize_t KeyIndex,
    _BDBT_BP(NodeReference_t) cnr,
    _BDBT_BP(NodeReference_t) Output
  ){
    #include "cpp/a.h"
  }

  /* query */
  static
  void
  q
  (
    _BDBT_BP(t) *list,
    #if defined(BDBT_set_KeySize)
      KeySize_t KeySize,
    #endif
    const void *Key,
    KeySize_t *KeyIndex,
    _BDBT_BP(NodeReference_t) *cnr
  ){
    #include "cpp/q.h"
  }

  static
  KeySize_t
  _r
  (
    _BDBT_BP(t) *list,
    #if defined(BDBT_set_KeySize)
      KeySize_t KeySize,
    #endif
    void *Key,
    _BDBT_BP(NodeReference_t) *cnr
  ){
    #include "cpp/r.h"
  }
  static
  void
  r
  (
    _BDBT_BP(t) *list,
    #if defined(BDBT_set_KeySize)
      KeySize_t KeySize,
    #endif
    void *Key,
    _BDBT_BP(NodeReference_t) cnr
  ){
    _r(
      list,
      #if defined(BDBT_set_KeySize)
        KeySize,
      #endif
      Key,
      &cnr
    );
  }
  /* remove with info */
  static
  KeySize_t
  rwi
  (
    _BDBT_BP(t) *list,
    #if defined(BDBT_set_KeySize)
      KeySize_t KeySize,
    #endif
    void *Key,
    _BDBT_BP(NodeReference_t) *cnr
  ){
    return _r(
      list,
      #if defined(BDBT_set_KeySize)
        KeySize,
      #endif
      Key,
      cnr
    );
  }

  /* confident query */
  static
  void
  cq
  (
    _BDBT_BP(t) *list,
    #if defined(BDBT_set_KeySize)
      KeySize_t KeySize,
    #endif
    const void *Key,
    _BDBT_BP(NodeReference_t) *cnr
  ){
    #include "cpp/cq.h"
  }

  /* give 0 if you want to sort from low, 1 for high. */
  struct Traverse_t{
    KeySize_t Current;
    struct ta_t{
      _BDBT_BP(NodeReference_t) n;
      _BDBT_bip(_neit_t) k;
    };
    #if !defined(BDBT_set_KeySize) || defined(BDBT_set_MaxKeySize)
      ta_t ta[MaxKeySize / BDBT_set_BitPerNode];
    #else
      static uintptr_t GetTraverseArraySize(KeySize_t KeySize){
        return KeySize / BDBT_set_BitPerNode;
      }
    #endif

    _BDBT_BP(NodeReference_t) Output;

    /* init */
    template <BitOrder_t BitOrder = BitOrderAny>
    void
    i
    (
      #if defined(BDBT_set_KeySize) && !defined(BDBT_set_MaxKeySize)
        ta_t *ta,
      #endif
      _BDBT_BP(NodeReference_t) rnr
    ){
      Current = 0;
      ta[0].k = BitOrder == BitOrderHigh ? _BDBT_ElementPerNode - 1 : 0;
      ta[0].n = rnr;
    }
    void
    i0
    (
      #if defined(BDBT_set_KeySize) && !defined(BDBT_set_MaxKeySize)
        ta_t *ta,
      #endif
      _BDBT_BP(NodeReference_t) rnr,
      BitOrder_t BitOrder = BitOrderAny
    ){
      if(BitOrder == BitOrderLow){
        i<BitOrderLow>(
          #if defined(BDBT_set_KeySize) && !defined(BDBT_set_MaxKeySize)
            ta,
          #endif
          rnr
        );
      }
      else if(BitOrder == BitOrderHigh){
        i<BitOrderHigh>(
          #if defined(BDBT_set_KeySize) && !defined(BDBT_set_MaxKeySize)
            ta,
          #endif
          rnr
        );
      }
      else{
        i<>(
          #if defined(BDBT_set_KeySize) && !defined(BDBT_set_MaxKeySize)
            ta,
          #endif
          rnr
        );
      }
    }

    /* traverse */
    template <BitOrder_t BitOrder = BitOrderAny>
    bool
    t
    (
      _BDBT_BP(t) *list,
      #if defined(BDBT_set_KeySize)
        #if !defined(BDBT_set_MaxKeySize)
          ta_t *ta,
        #endif
        KeySize_t KeySize,
      #endif
      void *Key
    ){
      #include "cpp/t.h"
    }

    bool
    t0(
      _BDBT_BP(t) *list,
      #if defined(BDBT_set_KeySize)
        #if !defined(BDBT_set_MaxKeySize)
          ta_t *ta,
        #endif
        KeySize_t KeySize,
      #endif
      void *Key,
      BitOrder_t BitOrder = BitOrderAny
    ){
      if(BitOrder == BitOrderLow){
        return t<0>(
          list,
          #if defined(BDBT_set_KeySize)
            #if !defined(BDBT_set_MaxKeySize)
              ta_t *ta,
            #endif
            KeySize,
          #endif
          Key
        );
      }
      else if(BitOrder == BitOrderHigh){
        return t<1>(
          list,
          #if defined(BDBT_set_KeySize)
            #if !defined(BDBT_set_MaxKeySize)
              ta_t *ta,
            #endif
            KeySize,
          #endif
          Key
        );
      }
      else{
        return t<>(
          list,
          #if defined(BDBT_set_KeySize)
            #if !defined(BDBT_set_MaxKeySize)
              ta_t *ta,
            #endif
            KeySize,
          #endif
          Key
        );
      }
    }
  };

  #undef BeforeLast
  #undef KeySize
  #undef _BDBT_ksizeConstexpr
};
