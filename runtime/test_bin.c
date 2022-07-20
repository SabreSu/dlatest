/*Copyright [2022-07-17] <wumeng>*/
#include <stdio.h>
#include <stdlib.h>
#include "test_bin.h"
#include "load.h"
#include "soft_fun.h"
int write_DLA() {
    printf("========write_DLA=======\n");
    struct CMD_Head cmd_head_dla1 = {24, 1, 2, 0};
    char cmd_data_dla1 = '0';
    struct CMD_Head cmd_head_dla2 = {8, 1, 3, 0};
    char cmd_data_dla2 = '0';
    int size_head = sizeof(struct CMD_Head);
    int size_data_dla = sizeof(char);
    // write dla type file
    FILE *fp = fopen("bin_dla.dat", "wb");
    printf("write DLA file name:%s\t\n", "bin_dla.dat");
    if (fp != NULL) {
        int count1 = fwrite(&cmd_head_dla1, size_head, 1, fp);
        int count2 = fwrite(&cmd_data_dla1, size_data_dla, 24, fp);
        printf("write DLA file data1 length:%d\t\n", count2);
        int count3 = fwrite(&cmd_head_dla2, size_head, 1, fp);
        int count4 = fwrite(&cmd_data_dla2, size_data_dla, 8, fp);
        printf("write DLA file data2 length:%d\t\n", count4);
    }
    fclose(fp);
    return 0;
}
int write_CPU() {
    printf("========write_CPU=======\n");
    struct CMD_Head cmd_head_cpu1 = {24, 0, 0, 0};
    int *read1 = (int *)malloc(27 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int l = 0; l < 3; l++) {
                *(read1 + i * 3 * 3 + j * 3 + l) = rand() % 10;
            }
        }
    }
    int *write1 = (int *)malloc(27 * sizeof(int));
    printf("write cpu file_read1 addr: %p\t\n", read1);
    printf("write cpu file_write1 addr: %p\t\n", write1);
    int *factor_addr1 = (int *)malloc(27 * sizeof(int));
    struct CMD_Data cmd_data_cpu1 = {0, 1, 27, 3, 3, read1,
                                     write1, factor_addr1, 24};
    struct CMD_Head cmd_head_cpu2 = {24, 0, 1, 0};
    int *read2 = (int *)malloc(48 * sizeof(int));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int l = 0; l < 3; l++) {
                *(read2 + i * 4 * 3 + j * 3 + l) = rand() % 10;
            }
        }
    }
    int *write2 = (int *)malloc(48 * sizeof(int));
    printf("write cpu file_read2 addr: %p\t\n", read2);
    printf("write cpu file_write2 addr: %p\t\n", write2);
    int *factor_addr2 = (int *)malloc(27 * sizeof(int));
    struct CMD_Data cmd_data_cpu2 = {0, 1, 48, 4, 4,
                                     read2, write2, factor_addr2, 24};

    int size_head = sizeof(struct CMD_Head);
    int size_data_cpu = sizeof(struct CMD_Data);
    //write cpu type file
    FILE *fp = fopen("bin_cpu.dat", "wb");
    printf("write CPU file name:%s\t\n", "bin_cpu.dat");
    if (fp != NULL) {
        int count1 = fwrite(&cmd_head_cpu1, size_head, 1, fp);
        int count2 = fwrite(&cmd_data_cpu1, size_data_cpu, 1, fp);
        int count5 = fwrite(&cmd_head_cpu2, size_head, 1, fp);
        int count6 = fwrite(&cmd_data_cpu2, size_data_cpu, 1, fp);
    }
    fclose(fp);
    return 0;
}
int write_DLA_AND_CPU() {
    printf("========write_DLA_AND_CPU=======\n");
    struct CMD_Head cmd_head_cpu1 = {24, 0, 0, 0};
    int *read1 = (int *)malloc(27 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int l = 0; l < 3; l++) {
                *(read1 + i * 3 * 3 + j * 3 + l) = rand() % 10;
            }
        }
    }
    int *write1 = (int *)malloc(27 * sizeof(int));
    printf("write dla&cpu file_read addr: %p\t\n", read1);
    printf("write dla&cpu file_write addr: %p\t\n", write1);
    int *factor_addr1 = (int *)malloc(27 * sizeof(int));
    struct CMD_Data cmd_data_cpu1 = {0, 1, 27, 3, 3, read1,
                                     write1, factor_addr1, 24};

    struct CMD_Head cmd_head_dla1 = {4, 1, 2, 0};
    char cmd_data_dla1 = '0';


    int size_head = sizeof(struct CMD_Head);
    int size_data_cpu = sizeof(struct CMD_Data);
    int size_data_dla = sizeof(char);
    // write dla_cpu type file
    FILE *fp = fopen("bin_dla_cpu.dat", "wb");
    printf("write DLA_CPU file name:%s\t\n", "bin_dla_cpu.dat");
    if (fp != NULL) {
        int count1 = fwrite(&cmd_head_cpu1, size_head, 1, fp);
        int count2 = fwrite(&cmd_data_cpu1, size_data_cpu, 1, fp);
        int count3 = fwrite(&cmd_head_dla1, size_head, 1, fp);
        int count4 = fwrite(&cmd_data_dla1, size_data_dla, 4, fp);
    }
    fclose(fp);
    return 0;
}
int main() {
    // test DLA type
    write_DLA();
    read_bin("bin_dla.dat");
    // test CPU type
    write_CPU();
    read_bin("bin_cpu.dat");
    // test DLA MIX CPU type
    write_DLA_AND_CPU();
    read_bin("bin_dla_cpu.dat");
    return 0;
}
