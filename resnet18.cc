// output channel 1
// 1. 多组卷积核的计算流程完全一致，仅仅是权重数据不同，该部分重复的指令由谁处理
// 2. 卷积指令后面的权重数据由谁添加


/*--------------------------------------block_0_0---------------------------------------------*/
Row = 0
Column = 0
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1
    tile_H_W: 64(63+1) // 这里填padding前的大小还是padding后的大小？
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224*224
    tile_H_W: 64(63+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224)
    src: DramAddr1 + 224*224*2
    tile_H_W: 64(63+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    WB Byte per channel: 224*224 // 这个是干嘛用的？
    post processing: quantize
    kernel size: 1*3*3
    output shape: 63*63*int8
};

/*--------------------------------------block_0_1---------------------------------------------*/
Row = 0
Column = 1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 63
    src: DramAddr1 + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    WB Byte per channel: 224*224 
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_0_2---------------------------------------------*/
Row = 0
Column = 2
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 63 + 62  -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 63 + 62
    src: DramAddr1 + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_0_3---------------------------------------------*/
Row = 0
Column = 3
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 63 + 62 + 62
    src: DramAddr1 + 63 + 62 + 62 -1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    Accu C: FastAddr1
    WB Byte per line: 224
    WB Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*37*int8
};

/*--------------------------------------block_1_0---------------------------------------------*/
Row = 1
Column = 0

// block_2_1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * 63 * Row
    tile_H_W: 64(63+1) // 这里填padding前的大小还是padding后的大小？
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row
    tile_H_W: 64(63+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row
    src: DramAddr1 + 224 * Row
    tile_H_W: 64(63+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 63*63*int8
};

/*--------------------------------------block_1_1---------------------------------------------*/
Row = 1
Column = 1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_1_2---------------------------------------------*/
// replace_layer_1_1_1
Row = 1
Column = 2

conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62  -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63 + 62
    src: DramAddr1 + 224 * Row + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_1_3---------------------------------------------*/
Row = 1
Column = 3
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63 + 62 + 62
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 -1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*37*int8
};
/*--------------------------------------block_2_0---------------------------------------------*/
Row = 2
Column = 0

// block_2_1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row
    tile_H_W: 64(63+1) // 这里填padding前的大小还是padding后的大小？
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row
    tile_H_W: 64(63+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row
    src: DramAddr1 + 224 * Row
    tile_H_W: 64(63+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 63*63*int8
};

/*--------------------------------------block_2_1---------------------------------------------*/
Row = 2
Column = 1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_2_2---------------------------------------------*/
// replace_layer_1_1_1
Row = 2
Column = 2

conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62  -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63 + 62
    src: DramAddr1 + 224 * Row + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_2_3---------------------------------------------*/
Row = 2
Column = 3
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63 + 62 + 62
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 -1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*37*int8
};

/*--------------------------------------block_3_0---------------------------------------------*/
Row = 3
Column = 0

// block_2_1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row
    tile_H_W: 38(37+1) // 这里填padding前的大小还是padding后的大小？
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row
    tile_H_W: 38(37+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    kernel size: 1*3*3
    output shape: 63*63*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row
    src: DramAddr1 + 224 * Row
    tile_H_W: 38(37+1)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [1,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 63*63*int8
};

/*--------------------------------------block_1_1---------------------------------------------*/
Row = 1
Column = 1
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63
    src: DramAddr1 + 224 * Row + 63 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_1_2---------------------------------------------*/
// replace_layer_1_1_1
Row = 1
Column = 2

conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62  -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    kernel size: 1*3*3
    output shape: 62*62*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63 + 62
    src: DramAddr1 + 224 * Row + 63 + 62 -1
    tile_H_W: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,0,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*62*int8
};

/*--------------------------------------block_1_3---------------------------------------------*/
Row = 1
Column = 3
// replace_layer_1_1_1
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_2
conv3x3 {
    dst: FastAddr1
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 - 1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    kernel size: 1*3*3
    output shape: 62*37*bf16
};

// replace_layer_1_1_3
conv3x3 {
    dst: DramAddr2(DramAddr1 + 3*224*224) + 224 * Row + 63 + 62 + 62
    src: DramAddr1 + 224 * Row + 63 + 62 + 62 -1
    tile_W: 39(37+2)
    tile_H: 64(62+2)
    channel num: 1
    In Byte per line: 224
    In Byte per channel: 224*224
    padding: [0,1,1,0]
    Accu C: FastAddr1
    In Byte per line: 224
    In Byte per channel: 224*224
    post processing: quantize
    kernel size: 1*3*3
    output shape: 62*37*int8
};

