#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include <chrono>

/* Couldn't get boost to work
#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>
*/

template<typename R>
bool is_ready(std::future<R> const& f) {
    return f.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready; 
}


int N = 1e3, M = 1e4;

void fill_big_guy(std::vector<std::vector<int>>& big_guy) {
    std::cout << "Starting fill." << std::endl;

    for(int i = 0; i < N; ++i) {
        big_guy.push_back(std::vector<int>());
        for(int j = 0; j < M; ++j) {
            big_guy[i].push_back(rand() % 1000);
        }
    } 

    std::cout << "Filling done." << std::endl;
}

void sort_big_guy(std::vector<std::vector<int>>& big_guy) {
    std::cout << "Starting sort." << std::endl;

    for(int i = 0; i < N; ++i) {
        sort(big_guy[i].begin(), big_guy[i].end());
    }

    std::cout << "Sorting done." << std::endl;
}

int main() {
    std::vector<std::vector<int>> big_guy;
    /* Couldn't get boost to work
    auto wrapper_with_params = boost::bind(fill_big_guy, boost::ref(big_guy));
    */
    auto fill = std::async(std::launch::async, fill_big_guy, std::ref(big_guy));
    bool is_fill_done = false;
    bool is_sort_started = false, is_sort_done = false;
    std::future<void> sort;

    while (!is_sort_done) {
        if (is_sort_started) {
            is_sort_done = is_ready(sort); 
            std::cout << "Sorting status: " << is_sort_done << std::endl;
        }
        else {
            is_fill_done = is_ready(fill); 
            std::cout << "Filling status: " << is_fill_done << std::endl;
            if (is_fill_done) {
                sort = std::async(std::launch::async, sort_big_guy, std::ref(big_guy));
                is_sort_started = true;
            }
        }

        std::cout << "Doing some computations..." << std::endl;
        int s = 0;
        for(int i = 0; i < 5 * 1e6; ++i)
            s += rand() % 1000;

        //std::cout << "Here is a sum of 5 million random numbers from 0 to 1000: " << s << std::endl;
    }

    std::cout << "Big guy preview:" << std::endl;
    std::cout << big_guy[0][0] << ' ' << big_guy[0][M - 1] << std::endl;
    std::cout << big_guy[N - 1][0] << ' ' << big_guy[N - 1][M - 1] << std::endl;

    return 0;
}