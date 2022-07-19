# Copyright [2022] <USTC-CSS lab>
"""Test cases about conv_nhwc"""
# pylint: disable=wrong-import-position
import sys
sys.path.append("../")
# pylint: disable=unused-wildcard-import, wildcard-import
from util import *  

import tvm

# pylint: disable=line-too-long,missing-function-docstring,too-many-arguments
def verify_conv_nhwc_int8(feature_map_shape, weight_shape, origin_file, dtype="int8", stride=1, padding=1):
  cmd_str = "../../assembler/as operators/{}".format(origin_file)
  as_out = "as_out"
  as_out = call_assembler(cmd_str, as_out)
  # generate "cmd.dat" file.
  # 1. get command fields from assembler output.
  param_dic = get_cmd_fields(as_out)
  # 2. translate command data form.
  param_dic = translate_cmd_data_form(param_dic)
  # 3. generate weight data.
  weight_list = gen_weight_data(weight_shape, dtype)
  weight_list_str = gen_weight_data_str(weight_list)
  
  # (fixme)TODO(ssb)：When the assembler is finished, change this step to
  #                   write the weight data into the weight file. And execute
  #                   the assembler after this step, taking the weight data
  #                   file as an input of the assembler.
  # write_weight_file(weight_list_str)

  # 4. write command and weight data to "cmd.dat" file.
  write_command(param_dic, weight_list_str, "cmd.dat")

  # generate "data.dat" file.
  feature_map = gen_feature_map_data(feature_map_shape, dtype)
  feature_map_str = numpyint8_2_hexstring(feature_map)
  write_data(feature_map_str, "data.dat")

  # verify the output of "sxdla"
  # 1. get result of python conv.
  dw_np = tvm.topi.testing.dilate_python(weight_list, (1, 1, 1, 1))
  b_np = tvm.topi.testing.conv2d_nhwc_python(feature_map, dw_np, stride, padding)

  # 2. run "sxdla"
  subprocess.run("sxdla", shell=True)

  subprocess.run("cp data.dat mem.dat", shell=True)
  # 3.verify the result
  # try:
  #   verify_result(b_np, [1, 56, 56, 1], "mem.dat")
  # except Exception as e:
  #   print(e)
  verify_result(b_np, [1, 56, 56, 1], "mem.dat")


def test_conv_nhwc_int8():
  verify_conv_nhwc_int8([1, 56, 56, 1], [3, 3, 1, 1], "conv_nhwc_int8_56")
  verify_conv_nhwc_int8([1, 28, 28, 1], [3, 3, 1, 1], "conv_nhwc_int8_28")
  verify_conv_nhwc_int8([1, 64, 64, 1], [3, 3, 1, 1], "conv_nhwc_int8_64")
  # clean up temporary files.
  clean_up_tmp_files()


if __name__ == "__main__":
  test_conv_nhwc_int8()
