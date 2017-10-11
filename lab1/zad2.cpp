#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
using namespace std;


float error(float expected, float real){
    return expected - real;
}

float relative_error(float expected, float real){
    return abs((expected - real) / expected);
}

float kahan_sum(float* tab, int size){
    float sum = 0.0f;
    float err = 0.0f;
    for (int i = 0; i < size; ++i){
        float y = tab[i] - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

float recursive_sum(float* tab, int size){
    if(size == 1)
        return tab[0];
    int mid = size / 2;
    return recursive_sum(tab, mid) + recursive_sum(tab + mid, size - mid);
}

int main(){
    unsigned long int N = 10000000000;
    cout << N << endl;
    float* tab = new float[N];
    float v = 0.53125;
    float goal = v * (float) N;
    cout << "Goal: " << goal << endl;
    for(unsigned long int i = 0; i < N; i++)
        tab[i] = v;

    const clock_t begin_time = clock();
    float sum = recursive_sum(tab, N);
    cout << "Recursive sum time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    const clock_t begin_timeK = clock();
    float sumK = kahan_sum(tab, N);
    cout << "Kahan sum time: " << float( clock () - begin_timeK ) /  CLOCKS_PER_SEC << endl;
    cout << "Sum: " << sum << endl;
    cout << "Error: " << error(goal, sum);
    cout << "Relative error: " << relative_error(goal, sum) << endl;
}
