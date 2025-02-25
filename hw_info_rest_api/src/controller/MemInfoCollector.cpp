#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "MemInfoCollector.h"


MemInfoCollector::MemInfoCollector()
{
    std::ifstream memProcFile;
        memProcFile.open("/proc/meminfo");
        if (!memProcFile.is_open()) {
		  throw std::runtime_error("Cannot open /proc/meminfo");
        }
        std::string line;
        while (std::getline(memProcFile, line)) {
          auto postotal = line.find("MemTotal");
          if (postotal!=std::string::npos) {
            fillParams(memTotal_, line);
            continue;
          }

          auto posfree = line.find("MemFree");
          if (posfree!=std::string::npos) {
            fillParams(memFree_, line);
            continue;
          }

          auto posavail = line.find("MemAvailable");
          if (posavail!=std::string::npos) {
            fillParams(memAvailable_, line);
            continue;
          }

          auto posswaptotal = line.find("SwapTotal");
          if (posswaptotal!=std::string::npos) {
            fillParams(swapTotal_, line);
            continue;
          }

          auto posswapfree = line.find("SwapFree");
          if (posswapfree!=std::string::npos) {
            fillParams(swapFree_, line);
            continue;
          }

        }
}

void MemInfoCollector::fillParams(std::string &param, const std::string& line) {

    const std::vector<int> v{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const auto valuepos = std::find_first_of(line.begin(), line.end(), v.begin(), v.end());
    const uint8_t parampos = line.find(*valuepos);
    param = line.substr(parampos, line.length());

}
std::string MemInfoCollector::memTotal() const {
  return memTotal_;
}
std::string MemInfoCollector::memFree() const {
  return memFree_;
}
std::string MemInfoCollector::swapTotal() const {
  return swapTotal_;
}
[[maybe_unused]] std::string MemInfoCollector::swapFree() const {
  return swapFree_;
}
std::string MemInfoCollector::memAvailable() const {
  return memAvailable_;
}

MemDescr::MemDescr(const std::string_view memTotal,
                   const std::string_view memFree,
                   const std::string_view memAvailable,
                   const std::string_view swapTotal,
                   const std::string_view swapFree) noexcept
    :
	memTotal_(memTotal),
	memFree_(memFree),
	memAvailable_(memAvailable),
	swapTotal_(swapTotal),
	swapFree_(swapFree)

{}

std::string MemDescr::memFree() const{
    return memFree_;
}

std::string MemDescr::memTotal() const{
    return memTotal_;
}

std::string MemDescr::memAvailable() const{
    return memAvailable_;
}

std::string MemDescr::swapFree() const{
    return swapFree_;
}

std::string MemDescr::swapTotal() const{
  return swapTotal_;
}
