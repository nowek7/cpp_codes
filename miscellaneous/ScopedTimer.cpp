#include <chrono>
#include <iostream>

#define USE_TIMER 1

#if USE_TIMER
  #define MEASURE_FUNCTION() ScopedTimer timer{__func__}
#else
  #define MEASURE_FUNCTION()
#endif

class ScopedTimer
  {
  public:
    using ClockType = std::chrono::steady_clock;

    ScopedTimer(const char* func)
      :
      theFunctionName{func},
      theStart{ClockType::now()}
      {}

    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer(ScopedTimer&&) = delete;
    auto operator=(const ScopedTimer&) -> ScopedTimer& = delete;
    auto operator=(ScopedTimer&&) -> ScopedTimer& = delete;

    ~ScopedTimer()
      {
      using namespace std::chrono;

      auto stop = ClockType::now();
      auto ms = duration_cast<std::chrono::milliseconds>(stop - theStart).count();
      std::cout << ms << " ms " << theFunctionName <<  "\n";
      }

  private:
    const char* theFunctionName = {};
    const ClockType::time_point theStart = {};
  };

auto some_function()
  {
  MEASURE_FUNCTION();
  std::cout << "Do some work..." << '\n';
  }

int main()
  {
  some_function();
  }
