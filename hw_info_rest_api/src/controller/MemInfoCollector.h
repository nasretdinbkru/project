#pragma once
#include <string>


class MemInfoCollector {
 public:
  MemInfoCollector();
  MemInfoCollector(const MemInfoCollector& other) = default;
  MemInfoCollector& operator=(const MemInfoCollector&) = delete;
  MemInfoCollector&& operator=(const MemInfoCollector&&) = delete;
  virtual ~MemInfoCollector() = default;

  [[nodiscard]] std::string memTotal() const;
  [[nodiscard]] std::string memFree() const;
  [[nodiscard]] std::string memAvailable() const;
  [[nodiscard]] std::string swapTotal() const;
  [[nodiscard]] std::string swapFree() const;

 private:
  std::string memTotal_{};
  std::string memFree_{};
  std::string memAvailable_{};
  std::string swapTotal_{};
  std::string swapFree_{};


  static void fillParams(std::string& param, const std::string& line);
};

class MemDescr {
 public:
  MemDescr(std::string_view mem_total,
		   std::string_view memFree,
		   std::string_view memAvailable,
		   std::string_view swapTotal,
		   std::string_view swapFree);
  MemDescr() = delete;
  virtual ~MemDescr() =default;
  MemDescr& operator=(const MemDescr&) = delete;
  MemDescr&& operator=(const MemDescr&&) = delete;
  MemDescr(const MemDescr& other) = delete;

  [[nodiscard]] std::string memTotal() const;
  [[nodiscard]] std::string memFree() const;
  [[nodiscard]] std::string memAvailable() const;
  [[nodiscard]] std::string swapTotal() const;
  [[nodiscard]] std::string swapFree() const;

 private:
  const std::string memTotal_;
  const std::string memFree_;
  const std::string memAvailable_;
  const std::string swapTotal_;
  const std::string swapFree_;

};
