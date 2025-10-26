#include "rec_arr_tool.h"
#include <iostream>
#include <math.h>
using namespace std;


// double rec_arr[rec_arr_size];
double Pi = 3.14159265358979323846;
// double Fs = N;
double freq = 10.0;
// double T = 1.0 / Fs;

int bin_1, bin_2, bin_3;
float lev_1, lev_2, lev_3;



Rec_Arr_Tool::Rec_Arr_Tool()
{
    cout << "     ----->  this is from the conctrector" << endl;
    init_highest_bins();
    cout << arr_size << " = ARR_SIZE" << endl;
    cout << "     +++++++   ----->  this is END OF the conctrector" << endl;
}

void Rec_Arr_Tool::look_rec_arr(int beg, int end)
{
    // cout << endl << " < look_rec_arr      HAS RUN <"<< endl<< endl;
    cout << endl << "------------->    " << beg  << " { look_rec_arr  } " << end << endl;
    int i = beg;
    while (i < end) {
        cout << i << " >  " << rec_arr[i]<<endl;
        i++;
    }
}

void Rec_Arr_Tool:: zero_rec_arr(){
    cout << endl << " zero_rec_arr HAS RUN" << endl;
    int i = 0;
    while (i < 40) {
        rec_arr[i] = 0;
        cout << i <<"  "<< rec_arr[i]<<endl;
        i=i+1;
    }
    rec_arr[3] = 3.333;
}

void Rec_Arr_Tool:: make_sin(double freq ,int beg, int leng){
    int i = beg;
    int en = leng;
    cout << endl << "--------( " << freq << " Hz )-- " << beg <<" { make_sin  } " << en << endl;

    double T = 1/44100;
    while (i < en) {
        rec_arr[i] = sin(2 * Pi * freq * i /48000 ) ;
        // rec_arr[i] = i*2 ;
        cout << i <<" ~ "<< rec_arr[i]<<endl;
        i=i+1;
    }
}

void Rec_Arr_Tool::init_highest_bins(){
    bin_1 =0; bin_2 =0; bin_3 =0;
    lev_1 =0; lev_2 =0; lev_3 =0;
}

void Rec_Arr_Tool::save_highest_bins(int bin, float level){
    if(level < lev_3){
        return;}
    if(level < lev_2){
        lev_3 = level; bin_3 = bin;
        return;}
    if(level < lev_1){
        lev_3 = lev_2; bin_3 = bin_2; lev_2 = level; bin_2 = bin;
        return;}
    lev_3 = lev_2; bin_3 = bin_2; lev_2 = lev_1; bin_2 = bin_1; lev_1 = level; bin_1 = bin;
}







