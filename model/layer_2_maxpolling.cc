/*
* primitive operator: 
*   maxpooling:
*     input shape: 64*112*112
*     stride: 2
*     padding: 1
*     output channel: 64*56*56
*/

/* 
* replaced by the following operator
*/


/*
* operator:
*   maxpooling:
*     input shape: 64*112*112
*     output shape: 64*56*56
*/

DramAddr1 = DramAddr2
DramAddr2 = DramAddr2


for ( Row = 0; Row < 2; Row++) {
  for ( Column = 0; Column < 2; Column++) {
    maxpooling {
      dst: DramAddr2 + 112 * 28 *Row + 28 * Colum
      src: DramAddr1 + 112 * 56 *Row + 56 * Colum
      tile_W: 56 // 224 / 4
      tile_H: 56
      channel num: 64
      In Byte per line: 112
      In Byte per channel: 112*112
      WB Byte per line: 56
      WB Byte per channel: 56*56
      post processing: quantize
      output shape: 28*28*int8
    };
  }
}
