/*Copyright [2022-07-17] <wumeng>*/
#include <stdio.h>
#include "soft_fun.h"
#include "load.h"

int read_bin(char * bin_filename) {
  printf("========read_bin=======\n");
  // init command head size, body size
  int size_head = sizeof(struct CMD_Head);
  int size_data_cpu = sizeof(struct CMD_Data);
  int size_data_dla = sizeof(char);
  // open bin file
  FILE *fp = fopen(bin_filename, "rb+");
  printf("read_bin file name:%s\t\n", bin_filename);
  struct CMD_Head head;
  // analysis bin file
  if (fp != NULL) {
    while (fp != NULL && !feof(fp)) {
        // read head
      int count = fread(&head, size_head, 1, fp);
      if (count == 1) {
        printf("stream_length: %d\tcmd_type: %d\t\n",
        head.stream_length, head.cmd_type);
        int type = head.cmd_type;
        if (type == 0) {
          printf("处理cpu指令\n");
          // type == 0: body is cpu command
          struct CMD_Data cpu_data;
          // read cpu_type_body
          int count1 = fread(&cpu_data, size_data_cpu, 1, fp);
          if (count1 == 1) {
            printf("op_code: %d\tread_addr: %p\twrite_addr: %p\t\n",
            cpu_data.op_code, cpu_data.read_addr, cpu_data.write_addr);
            int opcode = cpu_data.op_code;
            if (opcode == 0) {
              // run pooling
              int channel = cpu_data.data_length / (
                cpu_data.tile_height * cpu_data.tile_width);
              printf("channel:%d\ttile_height:%d\ttile_width:%d\t\n",
                     channel, cpu_data.tile_height, cpu_data.tile_width);
              printf("执行平均池化\n");
              int *read = cpu_data.read_addr;
              int *write = cpu_data.write_addr;
              int height = cpu_data.tile_height;
              int width = cpu_data.tile_width;
              int result = average_pooling(read, write, channel, height, width);
              printf("average_pooling.result: %d\t\n", result);
            }
          }
        } else {
          // dla
          printf("处理dla指令\n");
          char * data_dla;
          int length = head.stream_length;
          int count1 = fread(&data_dla, size_data_dla, length, fp);
          printf("data_dla_length: %d\t", length);
          if (count1 == length) {
            // run dla
            printf("data_dla放入驱动执行\n");
          }
        }
      }
    }
  }
  fclose(fp);
  return 0;
}
