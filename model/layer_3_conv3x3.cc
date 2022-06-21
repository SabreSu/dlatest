/*
* operator: 
*   conv3x3:
*     input shape: 64*56*56
*     kernel shape: 64*64*3*3
*     output shape: 64*56*56
*/


/*
* DRam memory model:
*
* begin         DramAddr2   
* |    free     |           |
* ############################
* | 3*228*228   | 64*56*56  |
*/


DramAddr1 = DramAddr2
DramAddr2 = DramAddr2 + 64*56*56

for(out_channel=0; out_channel < 64; out_channel++, DramAddr2+=56*56) {
  #progma channel = 0
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1
    tile_W: 56
    tile_H: 56
    channel num: 1
    In Byte per line: 56
    In Byte per channel: 56*56
    padding: [1,1,1,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 1
  conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 56*56*channel
    tile_W: 56
    tile_H: 56
    channel num: 62
    In Byte per line: 56
    In Byte per channel: 56*56
    padding: [1,1,1,1]
    kernel size: 1*3*3
    output shape: 56*56*bf16
  };

  #progma channel = 63
  conv3x3 {
    dst: DramAddr2
    src: DramAddr1 + 56*56*channel
    tile_W: 56
    tile_H: 56
    channel num: 1
    In Byte per line: 56
    In Byte per channel: 56*56
    padding: [1,1,1,1]
    Accu C: FastAddr1
    WB Byte per line: 56
    // WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 56*56*int8
  }
}

