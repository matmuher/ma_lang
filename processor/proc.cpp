#include <stdio.h>
#include "processor.h"
#include <time.h>

int main ()
    {
    size_t bin_size = 0;

    // *����� ������ ����� args cmd

    // LOGS AND BINARY OPEN
    FILE* bin = fopen ("binary_my_binary", "rb");
    FILE* log = fopen ("logs/stack_log.txt", "w");
    FILE* prc_log = fopen ("logs/prc_log.txt", "w");


    // READ SERVICE STRUCTURE
    bin_info ma_bin = {0, 0, 0};
    if (!fread (&ma_bin, sizeof (char), sizeof (ma_bin), bin))
        {
        puts ("[ERROR] Bad structure reading");
        }


    // VERIFY SERVICE STRUCTURE
    assert (ma_bin.signature == MY_SIGN);
    assert (ma_bin.version == version);


    // READ ASSEMBLED CODE
    bin_size = ma_bin.bin_size;
    int* cooking_list = (int*) calloc (bin_size, sizeof (int));
    if (!fread (cooking_list, sizeof (int), bin_size, bin))
        {
        puts ("[ERROR] Bad cmds' binary reading");
        }


    // PROC CONSTRUCT
    proc prc = {};
    proc_ctor (&prc, bin_size, cooking_list, log, prc_log);


    // clock_t execution_clock = clock();
    // CODE EXECUTE
    doer (&prc);
    // execution_clock = execution_clock - clock();
    // float execution_time = (float) execution_clock / CLOCKS_PER_SEC;
    // printf ("execution time: %.3f\n", execution_time);

    // LOGS AND BINARY CLOSE
    fclose (bin);
    fclose (log);
    fclose (prc_log);

    stop_inst_console_close ();
    }
