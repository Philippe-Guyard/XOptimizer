## **Summary of threading experiments:**

This was to get a "Hello, world!" application with multiple threads and compare `boost` and `std` libraries

The `std` library seems to have lots of tools for C++ multithreading (even tho some crucial things are missing, like the `.then` function from `boots`). The crucial difference is that `std` has a much better documentation, so we will probably stick to boost

To run the `std` program (`threading.cpp`), type:

    g++ -pthread threading.cpp -o threading && ./threading

To run the `boost` program (`threading_boost.cpp`), type:

    g++ -std=c++11 -lboost_thread -lpthread threading_boost.cpp -o threading_boost && ./threading_boost