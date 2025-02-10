#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

class Stopwatch {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point stopTime;
    bool isRunning;
    bool isCountdown;
    int countdownSeconds;

public:
    Stopwatch() : isRunning(false), isCountdown(false), countdownSeconds(0) {}

    // Memulai stopwatch untuk waktu maju
    void start() {
        if (!isRunning) {
            startTime = std::chrono::steady_clock::now();
            isRunning = true;
            isCountdown = false;
        }
    }

    // Menghentikan stopwatch
    void stop() {
        if (isRunning) {
            stopTime = std::chrono::steady_clock::now();
            isRunning = false;
        }
    }

    // Mengatur waktu mundur
    void setCountdown(int seconds) {
        countdownSeconds = seconds;
        startTime = std::chrono::steady_clock::now();
        isRunning = true;
        isCountdown = true;
    }

    // Mendapatkan waktu yang telah berlalu
    double getElapsedTime() {
        if (isRunning) {
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration<double>(currentTime - startTime);
            return elapsed.count();
        }
        auto elapsed = std::chrono::duration<double>(stopTime - startTime);
        return elapsed.count();
    }

    // Menjalankan timer mundur
    bool runCountdown() {
        if (isCountdown && isRunning) {
            double elapsed = getElapsedTime();
            int remainingTime = countdownSeconds - static_cast<int>(elapsed);

            if (remainingTime <= 0) {
                std::cout << "Waktu habis!" << std::endl;
                isRunning = false;
                return false;
            }

            std::cout << "Sisa waktu: " << remainingTime << " detik" << std::endl;
            return true;
        }
        return false;
    }

    // Menampilkan format waktu yang rapi
    void displayTime() {
        double time = getElapsedTime();
        int minutes = static_cast<int>(time) / 60;
        double seconds = time - (minutes * 60);

        std::cout << "Waktu: "
                  << std::setfill('0')
                  << std::setw(2) << minutes
                  << ":"
                  << std::setfill('0')
                  << std::setw(5) << std::fixed << std::setprecision(2)
                  << seconds
                  << std::endl;
    }
};

int main() {
    Stopwatch timer;
    int pilihan, detik;

    while (true) {
        std::cout << "\n--- Aplikasi Stopwatch ---" << std::endl;
        std::cout << "1. Mulai Stopwatch (Waktu Maju)" << std::endl;
        std::cout << "2. Atur Timer Mundur" << std::endl;
        std::cout << "3. Hentikan Stopwatch" << std::endl;
        std::cout << "4. Tampilkan Waktu" << std::endl;
        std::cout << "5. Keluar" << std::endl;
        std::cout << "Pilih opsi: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                timer.start();
                std::cout << "Stopwatch dimulai." << std::endl;
                break;
            case 2:
                std::cout << "Masukkan waktu mundur (detik): ";
                std::cin >> detik;
                timer.setCountdown(detik);
                while (timer.runCountdown()) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                break;
            case 3:
                timer.stop();
                std::cout << "Stopwatch dihentikan." << std::endl;
                break;
            case 4:
                timer.displayTime();
                break;
            case 5:
                std::cout << "Terima kasih!" << std::endl;
                return 0;
            default:
                std::cout << "Pilihan tidak valid." << std::endl;
        }
    }

    return 0;
}