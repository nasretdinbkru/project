#pragma once
#include <iostream>
#include <vector>
#include <string>

class CpuDescr {
 public:
  CpuDescr(std::string_view core_id,
		   std::string_view vendor,
		   std::string_view model,
		   std::string_view frequency) noexcept;
  CpuDescr() = delete;

  [[nodiscard]] std::string core_id() const;
  [[nodiscard]] std::string vendor() const;
  [[nodiscard]] std::string model() const;
  [[nodiscard]] std::string frequency() const;
  void set_core_id(const std::string& core_id);
  void set_vendor(const std::string& vendor);
  void set_model(const std::string& model);
  void set_frequency(const std::string& frequency);


 private:
  std::string core_id_;
  std::string vendor_;
  std::string model_;
  std::string frequency_;


};

class CpuInfoCollector {
 public:
  CpuInfoCollector();
  CpuInfoCollector& operator=(const CpuInfoCollector&) = delete;
  std::vector<CpuDescr> cpu_list();

 private:
  std::vector<CpuDescr> cpuInfoList_{};
};
