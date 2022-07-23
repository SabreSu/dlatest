import sys
from pathlib import Path
sys.path.append(str(Path(__file__).resolve().parents[3]))  # 将父级目录加入执行目录列表

from model.gen_dla import *

if __name__ == "__main__":
  tiling_test = gen_sxdla_code(
    "conv_nhwc_tiling_224",
    "weight",
    0x1000000,
    0x100000,
    224,
    224,
    56,
    56,
    4,
    3,
    3,
    ["conv3"]
  )

  tiling_test = gen_sxdla_code(
    "conv_nhwc_tiling_112",
    "weight",
    0x1000000,
    0x100000,
    112,
    112,
    56,
    56,
    2,
    3,
    3,
    ["conv3"]
  )