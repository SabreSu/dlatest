# Copyright [2022] <USTC-CSS lab>
"""Test cases about conv_nhwc"""
# pylint: disable=wrong-import-position
import sys
sys.path.append("../")
# pylint: disable=unused-wildcard-import, wildcard-import
from util import *  

import tvm

# pylint: disable=line-too-long,missing-function-docstring,too-many-arguments

def verify_conv_nhwc_relu(feature_map_shape, weight_shape, origin_file, weight_file, dtype="int8", stride=1, padding=1):
  # 1. Generate weight data and write to a weight file.
  weight_list = gen_weight_data(weight_shape, dtype)
  weight_list_str = gen_weight_data_str(weight_list)
  write_weight_file(weight_list_str, "weight.dat")
  
  # 2. Call assembler and generate a "bin" file.
  subprocess.run("as {} -w {} -o {}".format(origin_file, weight_file, "bin.dat"), shell=True)
  
  # 3. Remove the 64 bit data in the header of the bin file.
  with open('test.txt','a+',encoding='utf-8') as test:
    test.truncate(0)
  
  # 4. Generate input data and write to "data.dat" file.
  feature_map = gen_feature_map_data(feature_map_shape, dtype)
  feature_map_str = numpyint8_2_hexstring(feature_map)
  write_data(feature_map_str, "data.dat")
  
  # 5. Run dla
  subprocess.run("sxdla", shell=True)
  
  # 6. Parse "mem.dat" file and verify the result.
  dw_np = tvm.topi.testing.dilate_python(weight_list, (1, 1, 1, 1))
  b_np = tvm.topi.testing.conv2d_nhwc_python(feature_map, dw_np, stride, padding)
  b_np = b_np * (b_np > 0)
  verify_result(b_np, feature_map_shape, "mem.dat")

def test_conv_nhwc_relu():
  verify_conv_nhwc_relu([1, 64, 64, 1], [3, 3, 3, 3], "conv_nhwc_tiling_activate_64", "weight.dat")
  verify_conv_nhwc_relu([1, 112, 112, 1], [3, 3, 3, 3], "conv_nhwc_tiling_activate_112", "weight.dat")
  # clean up temporary files.
  clean_up_tmp_files()


if __name__ == "__main__":
  test_conv_nhwc_relu()
