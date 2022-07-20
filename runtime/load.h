/*Copyright [2022-07-17] <wumeng>*/
struct CMD_Head{
    short stream_length;
    char cmd_type;
    char cmd_id;
    int magic_number;
};
struct CMD_Data{
    char op_code;
    char data_type;
    short data_length;
    short tile_width;
    short tile_height;
    int *read_addr;
    int *write_addr;
    int *factor_offset_addr;
    int factor_length;
};
int read_bin(char * bin_filename);