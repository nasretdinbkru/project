#ifndef MEMINFOCOLLECTOR_H
#define MEMINFOCOLLECTOR_H
#include <string>

class MemDescr{
public:
  //IfDescr(const IfDescr&) = delete;
  MemDescr(const std::string_view memTotal,
          const std::string_view memFree,
          const std::string_view memAvailable,
          const std::string_view swapTotal,
          const std::string_view swapFree);

  std::string memTotal() const;
  std::string memFree() const;
  std::string memAvailable() const;
  std::string swapTolal() const;
  std::string swapFree() const;


  std::string mac_aadr();

private:
  const std::string _memTotal;
  const std::string _memFree;
  const std::string _memAvailable;
  const std::string _swapTolal;
  const std::string _swapFree;

};



class MemInfoCollector
{
public:
    MemInfoCollector();
private:
    std::string memTotal{};
    std::string memFree{};
    std::string memAvailable{};
    std::string swapTotal{};
    std::string swapFree{};
    static void fillParams(std::string &param, const std::string& line);
};

#endif // MEMINFOCOLLECTOR_H
