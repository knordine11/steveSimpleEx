#ifndef REC_ARR_TOOL_H
#define REC_ARR_TOOL_H

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

class Rec_Arr_Tool
{
public:
    Rec_Arr_Tool();
    static void look_rec_arr(int beg, int end);
    static void zero_rec_arr();
    static void make_sin(double freq ,int beg, int leng);
    static void init_highest_bins();
    static void save_highest_bins(int bin, float level);
};

#endif // REC_ARR_TOOL_H
