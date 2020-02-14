#include <cmath>
#include <vector>

std::vector<double> lomb_scargle(std::vector<double> flux, std::vector<double> time, std::vector<double> frequency, double variance){

    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;
    double flux_avg = std::accumulate( flux.begin(), flux.end(), 0llu)/ flux.size();
    std::vector<double> periodogram(frequency.size());


    for(int w = 0 ; w < frequency.size() ; w++){
        cos_sum_squared = 0llu;
        cos_squared_sum = 0llu;
        sin_sum_squared = 0llu;
        sin_squared_sum = 0llu;
        for (int i = 0 ; i < flux.size(); i++){
            double cos_result = cos(2* M_PI *frequency[w] * (time[i] - time[0]));
            double sin_result = sin(2* M_PI *frequency[w] * (time[i] - time[0]));
            cos_sum_squared += (flux[i] - flux_avg) * cos_result;
            cos_squared_sum += cos_result * cos_result;
            sin_sum_squared += (flux[i] - flux_avg) * sin_result;
            sin_squared_sum += sin_result * sin_result;
        }
        cos_sum_squared = cos_sum_squared * cos_sum_squared;
        sin_sum_squared = sin_sum_squared * sin_sum_squared;

        periodogram.at(w) = 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }

    return periodogram;
}

