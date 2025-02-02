#ifndef MEMINFOCOLLECTOR_H
#define MEMINFOCOLLECTOR_H
#include <string>
//


class MemInfoCollector
{
public:
    MemInfoCollector();

//	std::string memTotal(){
//	  return mem
//	}
  std::string memTotal{};
  std::string memFree{};
  std::string memAvailable{};
  std::string swapTotal{};
 private:
  std::string swapFree{};
    static void fillParams(std::string &param, const std::string& line);
};


class MemDescr{
 public:
  //IfDescr(const IfDescr&) = delete;
  MemDescr(std::string_view mem_total,
		   std::string_view memFree,
		   std::string_view memAvailable,
		   std::string_view swapTotal,
		   std::string_view swapFree);

  [[nodiscard]] std::string memTotal() const;
  [[nodiscard]] std::string memFree() const;
  [[nodiscard]] std::string memAvailable() const;
  [[nodiscard]] std::string swapTolal() const;
  [[nodiscard]] std::string swapFree() const;



 private:
  const std::string memTotal_;
  const std::string memFree_;
  const std::string memAvailable_;
  const std::string swapTolal_;
  const std::string swapFree_;

};


#endif // MEMINFOCOLLECTOR_H
