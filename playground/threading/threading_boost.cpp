#include <iostream>
#include <vector>
#include <algorithm>

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

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
    auto fill_wrapper_with_params = boost::bind(fill_big_guy, boost::ref(big_guy));
    boost::future<void> fill = boost::async(boost::launch::async ,fill_wrapper_with_params);

    boost::future<void> sort = fill.then(boost::launch::async, [&big_guy](boost::future<void> f) mutable {
        sort_big_guy(big_guy);
    });

    while (!sort.is_ready()) {
            std::cout << "Filling status: " << fill.get_state() << std::endl;
            std::cout << "Sorting status: " << sort.get_state() << std::endl;

        std::cout << "Doing some computations..." << std::endl;
        int s = 0;
        for(int i = 0; i < 5 * 1e6; ++i)
            s += rand() % 1000;

        //std::cout << "Here is a sum of 5 million random numbers from 0 to 1000: " << s << std::endl;
    }

    std::cout << "Big guy preview:" << std::endl;
    std::cout << big_guy[0][0] << ' ' << big_guy[0][M - 1] << std::endl;
    std::cout << big_guy[N - 1][0] << ' ' << big_guy[N - 1][M - 1] << std::endl;

    std::cout << "Filling status: " << fill.get_state() << std::endl;
    std::cout << "Sorting status: " << sort.get_state() << std::endl;


    return 0;
}