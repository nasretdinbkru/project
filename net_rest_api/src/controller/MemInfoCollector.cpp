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
          // TODO log error here
        }
        std::string line;
        while (std::getline(memProcFile, line)) {
          auto postotal = line.find("MemTotal");
          if (postotal!=std::string::npos) {
            fillParams(memTotal, line);
            continue;
          }

          auto posfree = line.find("MemFree");
          if (posfree!=std::string::npos) {
            fillParams(memFree, line);
            continue;
          }

          auto posavail = line.find("MemAvailable");
          if (posavail!=std::string::npos) {
            fillParams(memAvailable, line);
            continue;
          }

          auto posswaptotal = line.find("SwapTotal");
          if (posswaptotal!=std::string::npos) {
            fillParams(swapTotal, line);
            continue;
          }

          auto posswapfree = line.find("SwapFree");
          if (posswapfree!=std::string::npos) {
            fillParams(swapFree, line);
            continue;
          }

        }
}

void MemInfoCollector::fillParams(std::string &param, const std::string& line) {
    uint8_t colonPos = line.find(':');
    const std::string tmp = line.substr(colonPos + 1, line.length());
    const std::vector<int> v{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const auto valuepos = std::find_first_of(line.begin(), line.end(), v.begin(), v.end());
    const uint8_t parampos = line.find(*valuepos);
    param = line.substr(parampos, line.length());

}

MemDescr::MemDescr(const std::string_view memTotal,
                   const std::string_view memFree,
                   const std::string_view memAvailable,
                   const std::string_view swapTotal,
                   const std::string_view swapFree)
    :
      _memTotal(memTotal),
      _memFree(memFree),
      _memAvailable(memAvailable),
      _swapTolal(swapTotal),
      _swapFree(swapFree)

{}

std::string MemDescr::memFree() const{
    return _memFree;
}

std::string MemDescr::memTotal() const{
    return _memTotal;
}

std::string MemDescr::memAvailable() const{
    return _memAvailable;
}

std::string MemDescr::swapFree() const{
    return _swapFree;
}

std::string MemDescr::swapTolal() const{
    return _swapTolal;
}
