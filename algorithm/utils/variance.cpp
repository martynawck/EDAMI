// Created on 25-05-2016 by Michael nickson


#include <iostream>
#include <string>
#include <math.h>

class StdDeviation
{ 

private:
    int max;
    double value[100];
 
    double mean;
   
public:
 
    double CalculateMean()
    {
        double sum = 0;
        for(int i = 0; i < max; i++)
            sum += value[i];
        return (sum / max);
    }
 
    double CalculateVariane()
    {
        mean = CalculateMean();
 
        double temp = 0;
        for(int i = 0; i < max; i++)
        {
             temp += (value[i] - mean) * (value[i] - mean) ;
        }
        return temp / max;
    }
 
    double CalculateSampleVariane()
    {
        mean = CalculateMean();
 
        double temp = 0;
        for(int i = 0; i < max; i++)
        {
             temp += (value[i] - mean) * (value[i] - mean) ;
        }
        return temp / (max - 1);
    }
 
    int SetValues(double *p, int count)
    {
        if(count > 100)
            return -1;
        max = count;
        for(int i = 0; i < count; i++)
            value[i] = p[i];
        return 0;
    }
 
    double GetStandardDeviation()
    {
        return sqrt(CalculateVariane());
    }
 
    double GetSampleStandardDeviation()
    {
        return sqrt(CalculateSampleVariane());
    }
 
};
 
int main()
{
    double arrNumbers[] =
    {
        0.9,
        1.8,
        2.4,
        3.1,
        3.2,
        4.5,
        5.8,
        7.1
        
    };
 
    StdDeviation sd;
 
    sd.SetValues(arrNumbers, sizeof(arrNumbers) / sizeof(arrNumbers[0]));
 
    double mean = sd.CalculateMean();
    double variance = sd.CalculateVariane();
    double samplevariance = sd.CalculateSampleVariane();
    double sampledevi = sd.GetSampleStandardDeviation();
    double devi = sd.GetStandardDeviation();
 
    char buf[1024];
    sprintf(buf, "Total Numbers\t\t\t: %10d\n", sizeof(arrNumbers) / sizeof(arrNumbers[0]));
    std::cout << buf;
    sprintf(buf, "Mean\t\t\t\t: %10.5lf\nPopulation Variance\t\t: %10.4lf\n", mean, variance);
    std::cout << buf;
    sprintf(buf, "Sample variance\t\t\t: %10.4lf\n", samplevariance);
    std::cout << buf;
    sprintf(buf, "Population Standard Deviation\t: %10.4lf\n", devi);
    std::cout << buf;
    sprintf(buf, "Sample Standard Deviation\t: %10.4lf\n", sampledevi);
    std::cout << buf;
       
    return 0;
}
