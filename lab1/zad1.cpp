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

float simple_sum(float* tab, int N){
    ofstream myfile;
    myfile.open ("example.csv");
    float sum = 0.0;
    for(int i = 0; i < N; i++){
        sum += tab[i];
        if(i % 25000 == 0)
            myfile << i << ", " << relative_error((i+1)*tab[i], sum) << endl;
    }
    myfile.close();
    return sum;
}

float recursive_sum(float* tab, int size){
    if(size == 1)
        return tab[0];
    int mid = size / 2;
    return recursive_sum(tab, mid) + recursive_sum(tab + mid, size - mid);
}

int main(){
    unsigned long int N = 100000000;
    cout << N << endl;
    float* tab = new float[N];
    float v = 0.53125;
    float goal = v * (float) N;
    cout << "Goal: " << goal << endl;
    for(unsigned long int i = 0; i < N; i++)
        tab[i] = v;

    const clock_t begin_time = clock();
    float sum = simple_sum(tab, N);
    cout << "Simple sum time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    const clock_t begin_timeR = clock();
    float rec_sum = recursive_sum(tab, N);
    cout << "Recursive sum time: " << float( clock () - begin_timeR ) /  CLOCKS_PER_SEC << endl;
    cout << "-------" << endl;
    cout << "Sum: " << sum << endl;
    cout << "Recursively calculated sum: " << rec_sum << endl;
    cout << "Error: " << error(goal, sum) << endl;
    cout << "Relative error: " << relative_error(goal, sum) << endl;
    cout << "[Recursive] Error: " << error(goal, rec_sum) << endl;
    cout << "[Recursive] Relative error: " << relative_error(goal, rec_sum) << endl;
}
