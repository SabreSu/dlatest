/*
* primitive operator: 
*   conv7x7:
*     input shape: 3*224*224
*     kernel shape: 64*3*7*7
*     stride: 2
*     padding: 3
*     post processing: batch normal
*                      relu
*     output channel: 64*112*112
*/

/* 
* replaced by three operators
*/

/*
* FastRam memory model:
*
* FastAddr1     FastAddr2
* |             |
* ############################
*/

/*
* replace_layer_1:
*   maxpooling:
*     input shape: 64*224*224
*     output shape: 64*112*112
*/

DramAddr1 = DramAddr2
DramAddr2 = DramAddr2


for ( Row = 0; Row < 4; Row++) {
  for ( Column = 0; Column < 4; Column++) {
    maxpooling {
      dst: DramAddr2 + 224 * 28 *Row + 28 * Colum
      src: DramAddr1 + 224 * 56 *Row + 56 * Colum
      tile_W: 56 // 224 / 4
      tile_H: 56
      channel num: 64
      In Byte per line: 224
      In Byte per channel: 224*224
      WB Byte per line: 112
      WB Byte per channel: 112*112
      post processing: quantize
      output shape: 28*28*int8
    };
  }
}
