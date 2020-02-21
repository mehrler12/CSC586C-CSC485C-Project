#include <cmath>
#include <vector>

std::vector<double> lomb_scargle(std::vector<double> flux, std::vector<double> time, std::vector<double> frequency, double variance){

    int sample_size = flux.size();
    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;
    double flux_avg = std::accumulate( flux.begin(), flux.end(), 0llu)/ sample_size;
    std::vector<double> periodogram(frequency.size());

    double initial_time = time[0];
    for(int i = 0 ; i < sample_size ; i++){
        time[i] -= initial_time;
    }

    for(int i = 0 ; i< sample_size ; i++){
        flux[i] -= flux_avg;
    }

    for(int w = 0 ; w < frequency.size() ; w++){
        cos_sum_squared = 0llu;
        cos_squared_sum = 0llu;
        sin_sum_squared = 0llu;
        sin_squared_sum = 0llu;
        double frequency_2_pi = 2 * M_PI * frequency[w];
        for (int i = 0 ; i < sample_size ; i++){
            double frequency_2_pi_time = frequency_2_pi * time[i];
            double cos_result = cos(frequency_2_pi_time);
            cos_sum_squared += flux[i] * cos_result;
            cos_squared_sum += cos_result * cos_result;
            double sin_result = sin(frequency_2_pi_time);
            sin_sum_squared += flux[i] * sin_result;
            sin_squared_sum += sin_result * sin_result;
        }
        cos_sum_squared = cos_sum_squared * cos_sum_squared;
        sin_sum_squared = sin_sum_squared * sin_sum_squared;

        periodogram.at(w) = 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }

    return periodogram;
}

