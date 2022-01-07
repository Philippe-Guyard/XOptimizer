#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int bytes_downloaded = 0;

void download() {
    while (bytes_downloaded < 1e6) {
        bytes_downloaded += rand() % 10000;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    std::thread downloader(download);
    while (bytes_downloaded < 1e6) {
        cout << "Download progress: " << bytes_downloaded * 1.0 / 1e6 << endl;
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    downloader.join();
    return 0;
}