import sys
from pathlib import Path
sys.path.append(str(Path(__file__).resolve().parents[3]))  # 将父级目录加入执行目录列表

from model.gen_dla import *

if __name__ == "__main__":
  tiling_test = gen_sxdla_code(
    "conv_nhwc_tiling_maxpool_112",
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
    ["conv3", "maxpool"]
  )

  conv_activate = gen_sxdla_code(
    "conv_nhwc_maxpool_64",
    "weight",
    0x1000000,
    0x100000,
    64,
    64,
    64,
    64,
    1,
    3,
    3,
    ["conv3", "maxpool"]
  )