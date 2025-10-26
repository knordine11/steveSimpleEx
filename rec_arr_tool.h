#ifndef TEST_CLASS_1_H
#define TEST_CLASS_1_H

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

class Rec_Arr_Tool
{
public:
    Rec_Arr_Tool();
    // void look_rec_arr();
    void look_rec_arr(int beg, int end);
    void zero_rec_arr();
    void make_sin(double freq ,int beg, int leng);
    void init_highest_bins();
    void save_highest_bins(int bin, float level);
};

#endif // TEST_CLASS_1_H
