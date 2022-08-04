# Copyright [2022] <USTC-CSS lab>
"""Test the required tool function code."""

import os
import subprocess
import binascii
import numpy as np

import tvm
import tvm.topi.testing


def numpyint8_2_hexstring(bytes_list):
  """Convert numpy data of type int8 to hexadecimal string form.

  Args:
      bytes_list (list[bytes]): bytes list.

  Returns:
      list[string]: hexadecimal string list.
  """
  bytes_list = bytes_list.flatten()

  string_list = []
  for i in bytes_list:
    string_list.append(str(binascii.b2a_hex(i.tobytes()))[-3:-1])
  # print(string_list)
  return string_list

# The following functions are used to generate "cmd.dat" file.

# (fixme)TODO(ssb)：Confirm QWORD_LIST with zyj.
QWORD_LIST = [
    "Config",
    "Conv size",
    "Accu B Size",
    "Accu C Size",
    "Wb Size",
    "base_addr0",
    "base_addr1",
    "activa",
    "quanti"
]

def call_assembler(cmd_str, bin_name, echp_print=1):
  """Call the assembler to generate the binaries.

  Args:
      cmd_str (string): Commands that are executed at the command line.
      bin_name (string): The generated binary file name.
      echp_print (int, optional): Whether to print commands. Defaults to 1.

  Returns:
      _type_: _description_
  """
  if echp_print == 1:
    print("\nrun the cmd command : \"{}\"\n".format(cmd_str))

  # (fixme)TODO(ssb)：When the assembler is finished, change the
  #                   assembly command to the following form:

  # subprocess.run(cmd_str + " -o " + bin_name, shell=True)
  subprocess.run(cmd_str + " > " + bin_name, shell=True)

  return bin_name

def get_cmd_fields(bin_name):
  """Get each command field from the binary

  Args:
      bin_name (string): The generated binary file name.

  Returns:
      dict{qword:field}: Mapping from qword to field.
  """
  param_dic = {}

  with open(bin_name, 'r') as file:
    content = file.readlines()
    # print(content)
    for line in content:
      param = line.split(":")
      if len(param) == 2 and param[0] != "warning":
        # print(param)
        param_key = param[0]
        # print(param_key)
        param_value = param[1].split("\n")[0].strip()
        # print(param_value)
        param_dic[param_key] = param_value

  return param_dic

def translate_cmd_data_form(param_dic):
  """Translate command data form.

  Args:
      param_dic (dict): Mapping from qword to field.

  Returns:
      dict{qword:field}: Mapping from qword to field.
  """
  for key in param_dic.keys():
    param_dic[key] = param_dic[key].zfill(16)
    # print(key)
    # print(param_dic[key], " ", param_dic[key].encode('utf-8') )
    param_dic[key] = translate_2_little(param_dic[key])
    # print(key, ": ", param_dic[key])

  for qword in QWORD_LIST:
    if qword not in param_dic.keys():
      param_dic[qword] = ["00"]*8

  return param_dic

def translate_2_little(_str=""):
  """Converts the hexadecimal representation of a command to small end mode.

  Args:
      str (str, optional): The string that needs to be converted. Defaults to "".

  Returns:
      list[str]: An list of converted strings.
  """
  cmd_list = []
  for i in range(0, len(_str), 2):
    cmd_list.append(_str[i:i+2])

  cmd_list.reverse()
  return cmd_list

# (fixme)TODO(ssb): Call different numpy random generation
# functions according to different data types.
def gen_weight_data(dshape, dtype):
  """Generate weight data

  Args:
      dtype (string): The type of weight.
      dshape (list): The data shape of weight.

  Returns:
      ndarray[]: A data list of type numpy.
  """
  if dtype == "int8":
    under = -10
  elif dtype == "uint8":
    under = 0
  else:
    raise Exception("Currently, only \"int8\" and \"uint8\" data types are supported.")

  weight = np.random.randint(under, 10, size=dshape).astype(dtype)
  return weight

def gen_weight_data_str(weight):
  """_summary_

  Args:
      weight (ndarray[]): A data list of type numpy.

  Returns:
      list[string]: A string list in hexadecimal form.
  """
  # print(weight)
  weight = np.transpose(weight, (3,2,0,1))
  # print("---------------------")
  # print(weight)
  # weight = numpyint8_2_hexstring(weight)

  # if len(weight) % 8 != 0:
  #   zero_pad = ["00"]*(8-len(weight) % 8)
  #   weight += zero_pad

  return weight

def write_command(param_dic, weight, file_name="cmd.dat"):
  """Write the command data to the "cmd.dat" file.

  Args:
      param_dic (dict, optional): Mapping from qword to field.
      weight (list, optional): A string list in hexadecimal form.
      file_name (str, optional): The output file. Defaults to "cmd.dat".
  """
  with open(file_name, 'w', encoding="ascii") as file:
    for qword in QWORD_LIST:
      for i in param_dic[qword]:
        file.write(i + "\n")

    for i in weight:
      file.write(i + "\n")

  print("write command and weight data to \"{}\" file.".format(file_name))

def write_weight_file(weight_list_str, file_name="weight"):
  """_summary_

  Args:
      weight_list_str (list): The list of string of weight.
      file_name (str, optional): The file name to write. Defaults to "weight".

  Returns:
      string: file name
  """
  weight_list_str = weight_list_str.flatten()
  print("weight_List: ", weight_list_str)
  with open(file_name, 'wb') as file:
    for i in weight_list_str:
      print("weight_data: ",i,"---")
      file.write(i)

# The following functions are used to generate "data.dat" file.

# (fixme)TODO(ssb): Call different numpy random generation functions
# according to different data types.
def gen_feature_map_data(dshape, dtype):
  """Generate feature map data.

  Args:
      dshape (list): The data shape of feature map.
      dtype (string): The data type if feature map.

  Returns:
      ndarray[]: A data list of type numpy.
  """
  if dtype == "int8":
    under = -10
  elif dtype == "uint8":
    under = 0
  else:
    raise Exception("Currently, only \"int8\" and \"uint8\" data types are supported.")

  feature_map = np.random.randint(under, 10, size=dshape).astype(dtype)
  return feature_map

def write_data(feature_map, file_name="data.dat"):
  """Write the feature map data to the "cmd.dat" file.

  Args:
      feature_map (list, optional): The data of feature map.
      file_name (str, optional): The file name of feature map. Defaults to "data.dat".
  """
  with open("data.dat", 'w', encoding="ascii") as file:
    for i in feature_map:
      file.write(i + "\n")

  print("write feature map data to \"{}\" file.".format(file_name))

# (fixme)TODO(ssb): support the start adress are not equal to "0X1000000".
def verify_result(python_result, result_shape, file_name="mem.dat"):
  """Verify dla's data

  Args:
      python_result (ndarray): The result of python running.
      result_shape (_type_): The shape of result.
      file_name (str, optional): The file name of dla's result. Defaults to "mem.dat".
  """
  result_length = 1
  for i in result_shape:
    result_length *= i

  sx_result = []
  with open(file_name, 'r') as file:
    for i in range(result_length):
      _data = file.readline()[0:2]
      _hex = _data.encode("utf-8")
      _bin = binascii.unhexlify(_hex)
      np_form = np.frombuffer(_bin, dtype=np.int8)
      sx_result.append(np_form)

  sx_result_np = np.array(sx_result, dtype="int8")
  sx_result_np = sx_result_np.reshape(result_shape)

  tvm.testing.assert_allclose(sx_result_np, python_result, rtol=1e-5)

def clean_up_tmp_files():
  """Clean up temporary files.

  """
  pwd = os.getcwd()
  cmd_file = pwd + "/cmd.dat"
  data_file = pwd + "/data.dat"
  result_file = pwd + "/mem.dat"
  # as_out_file = pwd + "/as_out"

  if os.path.exists(cmd_file):
    os.remove(cmd_file)
    print(cmd_file, "has been removed.")

  if os.path.exists(data_file):
    os.remove(data_file)
    print(data_file, "has been removed.")

  if os.path.exists(result_file):
    os.remove(result_file)
    print(result_file, "has been removed.")

  # if os.path.exists(as_out_file):
  #   os.remove(as_out_file)
  #   print(as_out_file, "has been removed.")

def remove_head(file_name = "byte_per_line"):
  with open(file_name, 'r') as _file:
    cmds = _file.readlines()
    
  with open("cmd.dat", 'w') as _file:
    for cmd in cmds[8:]:
      _file.write(cmd)
      
