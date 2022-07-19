
tab_string = " "*2

class gen_sxdla_code():
  
  def __init__(self, file_name, weight_file, dst_addr, src_addr,
               input_width, input_height, tile_width, tile_height,
               tile_factor, input_channel, output_channel, op_list,
               add_addr=0x000000) -> None:
    self.file_name = file_name
    self.weight_file = weight_file
    self.dst_base_addr = dst_addr
    self.src_base_addr = src_addr
    self.input_width = input_width
    self.input_height = input_height
    self.input_channel = input_channel
    self.output_channel = output_channel
    self.tile_width = tile_width
    self.tile_height = tile_height
    self.tile_factor = tile_factor
    self.fast_addr0 = 0x2f000000
    self.fast_addr1 = 0x2f002000
    self.code_list = []
    self.op_list = op_list
    self.add_base_addr = add_addr
    self.gen_program()
    self.write_file(file_name)
    
    
  def gen_program(self):
    level = 0
    self.code_list.append("{\n")
    
    # self.code_list.append(self.gen_weight(level+1))
    
    # program head
    self.code_list.append(tab_string + "\"program\":\n")
    self.code_list.append(tab_string + "[\n")

    self.gen_out_channel(level+1)
    
    self.code_list.append(tab_string + "]\n")
    self.code_list.append("}\n")

  def gen_out_channel(self, level):
    for oc in range(self.output_channel):
      self.gen_layers(oc, level)
      
  def gen_layers(self, oc, level):
    for row in range(self.tile_factor):
      for column in range(self.tile_factor):
        if self.tile_factor == 1:
          padding = [1,1,1,1]
        else:
          padding = self.calcu_pad(row, column)
        self.gen_block(oc, row, column, padding, level+1)


  def calcu_pad(self, row, column):
    if row == 0:
      if column == 0:
        return [1, 1, 0, 0]
      elif column == self.tile_factor - 1:
        return [1, 0, 0, 1]
      else:
        return [1, 0, 0, 0]
    
    elif row == self.tile_factor - 1:
      if column == 0:
        return [0, 1, 1, 0]
      elif column == self.tile_factor - 1:
        return [0, 0, 1, 1]
      else:
        return [0, 0, 1, 0]
    
    else:
      if column == 0:
        return [0, 1, 0, 0]
      elif column == self.tile_factor - 1:
        return [0, 0, 0, 1]
      else:
        return [0, 0, 0, 0]
      

  def gen_weight(self, level):
    _str = "\"weight_file\":\"{}\",\n".format(self.weight_file) 
    return "  "*level + _str

  def gen_block(self, oc, row, column, padding, level):
    if "conv3" in self.op_list:
      #step 1.
      self.code_list.append(tab_string*level + "{\n")

      self.gen_input(row, column, 0, padding, level+1)
      if "add" in self.op_list:
        self.gen_other_addr(row, column, 0, padding, level+1)
      self.gen_operators(1, 0, padding, level+1, True)
      self.gen_output(hex(self.fast_addr0), level+1)
      
      self.code_list.append(tab_string*level + "},\n")

      #step 2.
      self.code_list.append(tab_string*level + "{\n")

      self.gen_input(row, column, 1, padding, level+1)
      if "add" in self.op_list:
        self.gen_other_addr(row, column, 0, padding, level+1)
      self.gen_operators(self.input_channel - 2, 1, padding, level+1, True)
      self.gen_output(hex(self.fast_addr0), level+1)

      self.code_list.append(tab_string*level + "},\n")

      #step 3.
      self.code_list.append(tab_string*level + "{\n")

      self.gen_input(row, column, self.input_channel - 1, padding, level+1)
      if "add" in self.op_list:
        self.gen_other_addr(row, column, 0, padding, level+1)
      self.gen_operators(1, self.input_channel - 1, padding, level+1, False)
      
      dst_addr = int(self.dst_base_addr) \
              + self.input_width * self.tile_height * row  \
              + self.tile_width * column  \
              + oc * self.input_width * self.input_height
                
      self.gen_output(hex(dst_addr), level+1)

      if (row == self.tile_factor-1 and column == self.tile_factor-1 and oc == self.output_channel-1):
        self.code_list.append(tab_string*level + "}\n")
      else:
        self.code_list.append(tab_string*level + "},\n")
    

  def gen_input(self, row, colum, ic, padding, level):
    self.code_list.append(tab_string*level + "\"input_addr\":\n")
    self.code_list.append(tab_string*level + "{\n")

    tile_top = 0
    tile_left = 0
    tile_bottom = 0
    tile_right = 0
    
    if padding[0] == 0:
      tile_top = 1
    
    if padding[1] == 0:
      tile_left = 1
      
    if padding[2] == 0:
      tile_bottom = 1
      
    if padding[3] == 0:
      tile_right = 1

    input_addr = int(self.src_base_addr) + self.input_width * self.input_height * ic  \
               + self.input_width * self.tile_height * row                            \
               + self.tile_width * colum                                              \
               + self.input_width * tile_top * (-1)                                   \
               + tile_left * (-1)
    
    self.code_list.append(tab_string*(level+1) + "\"tile_width\": {} ,\n".format(self.tile_width + tile_left + tile_right))
    self.code_list.append(tab_string*(level+1) + "\"tile_height\": {} ,\n".format(self.tile_height + tile_top + tile_bottom))
    
    self.code_list.append(tab_string*(level+1) +  "\"addr\":\"{}\",\n".format(hex(input_addr)))
    
    self.code_list.append(tab_string*(level+1) + "\"byte_perline\": {} ,\n".format(self.input_width))
    self.code_list.append(tab_string*(level+1) + "\"byte_perchan\": {}\n".format(self.input_width * self.input_height))
    
    self.code_list.append(tab_string*level + "},\n")

  def gen_other_addr(self, row, colum, ic, padding, level):
    self.code_list.append(tab_string*level + "\"other_addr\":\n")
    self.code_list.append(tab_string*level + "{\n")

    tile_top = 0
    tile_left = 0
    tile_bottom = 0
    tile_right = 0
    
    if padding[0] == 0:
      tile_top = 1
    
    if padding[1] == 0:
      tile_left = 1
      
    if padding[2] == 0:
      tile_bottom = 1
      
    if padding[3] == 0:
      tile_right = 1
    
    add_addr = int(self.add_base_addr) + self.input_width * self.input_height * ic  \
               + self.input_width * self.tile_height * row                            \
               + self.tile_width * colum                                              \
               + self.input_width * tile_top * (-1)                                   \
               + tile_left * (-1)

    
    
    self.code_list.append(tab_string*(level+1) + "\"tile_width\": {} ,\n".format(self.tile_width + tile_left + tile_right))
    self.code_list.append(tab_string*(level+1) + "\"tile_height\": {} ,\n".format(self.tile_height + tile_top + tile_bottom))
    
    self.code_list.append(tab_string*(level+1) +  "\"addr\":\"{}\",\n".format(hex(add_addr)))

    self.code_list.append(tab_string*(level+1) + "\"byte_perline\": {} ,\n".format(self.input_width))
    self.code_list.append(tab_string*(level+1) + "\"byte_perchan\": {}\n".format(self.input_width * self.input_height))
    
    self.code_list.append(tab_string*level + "},\n")

  def gen_operators(self, channel_num, ic, padding, level, conv_last):
    self.code_list.append(tab_string*level + "\"operators\":\n")
    self.code_list.append(tab_string*level + "{\n")
    
    if "conv3" in self.op_list:
      self.gen_conv(channel_num, ic, padding, level+1, conv_last)
    
    if conv_last == False:
      if "activate" in self.op_list:
        self.gen_active(level+1)
        
      if "maxpool" in self.op_list:
        self.gen_maxpool(level+1)

      self.gen_quantes(level+1)
    
    self.code_list.append(tab_string*level + "},\n")


  def gen_conv(self, channel_num, ic, padding, level, conv_last):
    self.code_list.append(tab_string*level + "\"conv3\":\n")
    self.code_list.append(tab_string*level + "{\n")
    
    self.code_list.append(tab_string*(level + 1) + "\"chan_num\": {},\n".format(str(channel_num)))
    self.code_list.append(tab_string*(level + 1) + "\"padding\": {}\n".format(str(padding)))
    
    if conv_last:
      self.code_list.append(tab_string*level + "}\n")
    else:
      self.code_list.append(tab_string*level + "},\n")


  def gen_active(self, level):
    self.code_list.append(tab_string*level + "\"activate\":\n")
    self.code_list.append(tab_string*level + "{\n")
    
    self.code_list.append(tab_string*(level + 1) + "\"pos_slope\": {},\n".format(str(1)))
    self.code_list.append(tab_string*(level + 1) + "\"neg_slope\": {},\n".format(str(1)))
    self.code_list.append(tab_string*(level + 1) + "\"pos_thd\": {}\n".format(str(255)))

    self.code_list.append(tab_string*level + "},\n")


  def gen_maxpool(self, level):
    self.code_list.append(tab_string*(level) + "\"maxpool\":{},\n")


  def gen_quantes(self, level):
    self.code_list.append(tab_string*level + "\"quantize\":\n")
    self.code_list.append(tab_string*level + "{\n")
    
    self.code_list.append(tab_string*(level +1) + "\"pos_slope\": {},\n".format(str(1)))
    self.code_list.append(tab_string*(level +1) + "\"neg_slope\": {}\n".format(str(1)))

    self.code_list.append(tab_string*level + "}\n")


  def gen_output(self, dst_addr, level):
    self.code_list.append(tab_string*level + "\"write_back\":\n")
    self.code_list.append(tab_string*level + "{\n")
    
    self.code_list.append(tab_string*(level + 1) + "\"addr\":\"{}\",\n".format(dst_addr))
    self.code_list.append(tab_string*(level + 1) + "\"byte_perline\": {},\n".format(str(self.tile_width)))
    self.code_list.append(tab_string*(level + 1) + "\"byte_perchan\": {}\n".format(str(self.tile_width * self.tile_height)))

    self.code_list.append(tab_string*level + "}\n") 

  def write_file(self, file_name):
    with open(file_name, 'w') as _file:
      for i in self.code_list:
        _file.write(i)
  

if __name__ == "__main__":
  code = gen_sxdla_code(
    "layer1_conv7x7",
    "weight",
    0x1000000,
    0x100000,
    224,
    224,
    56,
    56,
    4,
    3,
    64,
    ["conv3","activate","maxpool"]
  )

  code2 = gen_sxdla_code(
    "layer2_average_pool",
    "weight",
    0x1000000,
    0x1000000,
    112,
    112,
    56,
    56,
    2,
    64,
    64,
    ["conv3","maxpool"]
  )
  
  code3 = gen_sxdla_code(
    "layer3_56*56_1",
    "weight",
    0x1031000,
    0x1000000,
    56,
    56,
    56,
    56,
    1,
    64,
    64,
    ["conv3","maxpool"]
  )
  code4 = gen_sxdla_code(
    "layer4_56*56_2",
    "weight",
    0x1031000,
    0x1031000,
    56,
    56,
    56,
    56,
    1,
    64,
    64,
    ["conv3","maxpool"]
  )
  
  code5 = gen_sxdla_code(
    "layer5_56*56_3",
    "weight",
    0x1031000,
    0x1031000,
    56,
    56,
    56,
    56,
    1,
    64,
    64,
    ["conv3","maxpool"]
  )
  
  code6 = gen_sxdla_code(
    "layer6_56*56_3_resblock",
    "weight",
    0x1031000,
    0x1031000,
    56,
    56,
    56,
    56,
    1,
    64,
    64,
    ["conv3","add", "maxpool"],
    0x1000000
  )