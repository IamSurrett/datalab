#include <cstdio>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <random>
#include <map>

void fillWithRandomValues(std::vector<unsigned int> &vals) {
    for (auto &val : vals) { val = rand() % 1000000000; }
}

void randomNumberDemo() {
    // Seed with a real random value, if available
    std::random_device r;
 
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    int mean = uniform_dist(e1);
    std::cout << "Randomly-chosen mean: " << mean << '\n';
 
    // Generate a normal distribution around that mean
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()}; 
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 2);
 
    std::map<int, int> hist;
    for (int n = 0; n < 10000; ++n) {
        ++hist[std::round(normal_dist(e2))];
    }
    std::cout << "Normal distribution around " << mean << ":\n";
    for (auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
}

void printVector(const std::vector<unsigned int> &vals) {
#ifdef DEBUG
  for (auto val : vals) { printf("%u ", val);}
  puts("");
#endif
}

unsigned long long fibonacci(unsigned char c) { 
    return ((c<2)?1:fibonacci(c-1)+fibonacci(c-2));
}

// From https://en.cppreference.com/w/cpp/chrono
void timingDemo() {
    auto start = std::chrono::system_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

int main(int argc, const char *argv[]) {
    int cnt,N;
    
    if (argc < 2) { puts("usage: timeMerge vectorLength\nvectorLength > 0"); return 0; }
    N = atoi(argv[1]);
    if (N < 1) { puts("usage: timeMerge vectorLength\nvectorLength > 0"); return 0; }
    std::vector<unsigned int> vals(N);
    fillWithRandomValues(vals);
    printVector(vals);
    return 0;
}