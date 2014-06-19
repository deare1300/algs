#include "radar.h"
#include "header.h"
Radar::Radar()
{
    //ctor
}

Radar::~Radar()
{
    //dtor
}


vector<int> pps_times;
vector<int> gps_times;
// y = a1*x + a0;
/*
struct Line
{
    double a1;
    double a0;
};


static void square_line(struct Line *line, int target, int start, int end)
{
    double xy = 0.0, xsum = 0.0, ysum = 0.0, x_square_sum = 0.0;
    double x_ave, y_ave;
    int i;
    int total = end - start + 1;
    for(i = start; i <= end; ++i)
    {
        int x = (pps_times[i].tv_sec - pps_times[start].tv_sec)*1000000 + pps_times[i].tv_usec - pps_times[start].tv_usec;
        int y = (gps_times[i]-pps_times[i].tv_sec)*1000000 - pps_times[i].tv_usec;
        xy += x*y;
        xsum += x;
        ysum += y;
        x_square_sum += x*x;
    }
    x_ave = xsum / total;
    y_ave = ysum / total;
    line->a1 = (xy - total*x_ave*y_ave)/(x_square_sum - total*x_ave*x_ave);
    line->a0 = y_ave - line->a1*x_ave;
}

void test_radar()
{
    vector<int> x;
    vector<
}

*/
