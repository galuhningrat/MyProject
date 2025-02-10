// #include <iostream>

// memulai stopwatch untuk waktu maju
// menghentikan stopwatch
// mengatur waktu mundur
// mendapatkan waktu yang telah berlalu
// menjalankan waktu mundur
// menampilkan format waktu yang rapi

// C++ program to create a countdown timer
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
using namespace std;

// Function to get the current date and time as a string.
string getPresentDateTime()
{
    // Declare a time_t variable to hold the current time.
    time_t tt;
    // Declare a pointer to a tm struct to hold the local
    // time.
    struct tm* st;

    // Get the current time.
    time(&tt);
    // Convert the current time to local time.
    st = localtime(&tt);
    // Return the local time as a string.
    return asctime(st);
}

int main()
{
    // Declare an integer variable to hold the total number
    // of seconds for the counter.
    int seconds;

    // Prompt the user to enter the total number of seconds
    // for the counter.
    cout << "Enter total number seconds for the counter"
         << endl;
    cin >> seconds;

    // Loop until the counter reaches zero.
    while (seconds >= 1) {
        // Print the current value of the counter along with
        // the present date and time.
        cout << "Time Remaining : " << seconds
             << " : " + getPresentDateTime() << endl;

        // Pause the program execution for 1 second.
        this_thread::sleep_for(chrono::seconds(1));

        // Decrement the counter.
        seconds--;
    }
    cout << "Time's Up!" << endl;

    return 0;
}
