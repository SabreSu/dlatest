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
* replace_layer_2:
*   conv3x3:
*     input shape: 3*224*224
*     kernel shape: 3*3*3*3
*     output shape: 3*224*224
*/
TMP = DramAddr1
DramAddr1 = DramAddr2
DramAddr2 = DramAddr1

for(out_channel=0; out_channel < 3; out_channel++, DramAddr1+=224*224) {
  /*--------------------------------------block_0_0---------------------------------------------*/
  #progma Row = 0
  #progma Column = 0

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1
    tile_W: 56+1 // 224 / 4
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
      dst: FastAddr1
      src: DramAddr1 + 224*224
      tile_W: 56+1
      tile_H: 56+1
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,1,0,0]
      kernel size: 1*3*3
      output shape: 56*56*bf16
  };

  conv3x3 {
      dst: DramAddr2(DramAddr1 + 3*224*224)
      src: DramAddr1 + 224*224*2
      tile_W: 56+1
      tile_H: 56+1
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,1,0,0]
      Accu C: FastAddr1
      WB Byte per line: 224
      // WB Byte per channel: 224*224
      post processing: quantize
      kernel size: 1*3*3
      output shape: 56*56*int8
  };

  /*--------------------------------------block_0_1---------------------------------------------*/
  #progma Row = 0
  #progma Column = 1

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 56 - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224 + 56 - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 56
    src: DramAddr1 + 224*224*2 + 56 - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_0_2---------------------------------------------*/
  #progma Row = 0
  #progma Column = 2

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 56 * 2 - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224 + 56 * 2 - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 56 * 2
    src: DramAddr1 + 224*224*2 + 56 * 2 - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_0_3---------------------------------------------*/
  #progma Row = 0
  #progma Column = 3

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 56 * 3 - 1
    tile_W: 56+1
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224 + 56 * 3 - 1
    tile_W: 56+1
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 56 * 3
    src: DramAddr1 + 224*224*2 + 56 * 3 - 1
    tile_W: 56+1
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_1_0---------------------------------------------*/
  #progma Row = 1
  #progma Column = 0

  #progma channel = 0
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
    tile_W: 56+1 // 224 / 4
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 1
  conv3x3 {
      dst: FastAddr1
      src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
      tile_W: 56+1
      tile_H: 56+2
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,0,0,0]
      kernel size: 1*3*3
      output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
      dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row
      src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
      tile_W: 56+1
      tile_H: 56+2
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,0,0,0]
      Accu C: FastAddr1
      WB Byte per line: 224
      // WB Byte per channel: 224*224
      post processing: quantize
      kernel size: 1*3*3
      output shape: 56*56*int8
  };

  /*--------------------------------------block_1_1---------------------------------------------*/
  #progma Row = 1
  #progma Column = 1

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_1_2---------------------------------------------*/
  #progma Row = 1
  #progma Column = 2

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_1_3---------------------------------------------*/
  #progma Row = 1
  #progma Column = 3

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_2_0---------------------------------------------*/
  #progma Row = 2
  #progma Column = 0

  #progma channel = 0
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
    tile_W: 56+1 // 224 / 4
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 1
  conv3x3 {
      dst: FastAddr1
      src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
      tile_W: 56+1
      tile_H: 56+2
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,0,0,0]
      kernel size: 1*3*3
      output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
      dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row
      src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
      tile_W: 56+1
      tile_H: 56+2
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,0,0,0]
      Accu C: FastAddr1
      WB Byte per line: 224
      // WB Byte per channel: 224*224
      post processing: quantize
      kernel size: 1*3*3
      output shape: 56*56*int8
  };

  /*--------------------------------------block_2_1---------------------------------------------*/
  #progma Row = 2
  #progma Column = 1

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_2_2---------------------------------------------*/
  #progma Row = 2
  #progma Column = 2

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_2_3---------------------------------------------*/
  #progma Row = 2
  #progma Column = 3

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,0]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+2
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_3_0---------------------------------------------*/
  #progma Row = 3
  #progma Column = 0

  #progma channel = 0
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
    tile_W: 56+1 // 224 / 4
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,0,0,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 1
  conv3x3 {
      dst: FastAddr1
      src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
      tile_W: 56+1
      tile_H: 56+1
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,0,0,1]
      kernel size: 1*3*3
      output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
      dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row
      src: DramAddr1 + 224*224*channel + 224 * (56-1) * Row
      tile_W: 56+1
      tile_H: 56+1
      channel num: 1
      In Byte per line: 224
      In Byte per channel: 224*224
      padding: [1,0,0,1]
      Accu C: FastAddr1
      WB Byte per line: 224
      // WB Byte per channel: 224*224
      post processing: quantize
      kernel size: 1*3*3
      output shape: 56*56*int8
  };

  /*--------------------------------------block_3_1---------------------------------------------*/
  #progma Row = 3
  #progma Column = 1

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,1]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_3_2---------------------------------------------*/
  #progma Row = 1
  #progma Column = 2

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+2
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,0,1]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };

  /*--------------------------------------block_3_3---------------------------------------------*/
  #progma Row = 3
  #progma Column = 3

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 2
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 3
  conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * 56 * Row + 56*Column
    src: DramAddr1 + 224*224*channel + 224*(56-1)*Row + 56*Column - 1
    tile_W: 56+1
    tile_H: 56+1
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,0,1,1]
    Accu C: FastAddr1
    WB Byte per line: 224
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  };
}