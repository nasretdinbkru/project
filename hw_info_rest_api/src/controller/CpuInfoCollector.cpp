//
// Created by ray on 05.02.2025.
//

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include "CpuInfoCollector.h"

std::vector<CpuDescr> CpuInfoCollector::cpu_list() {
  return cpuInfoList_;
}

CpuInfoCollector::CpuInfoCollector() {

  std::ifstream cpuinfo("/proc/cpuinfo");
  std::string line;
  std::string model_name;
  std::string core_id;
  std::string frequency;
  std::string vendor;
  CpuDescr cpu_descr(core_id,vendor,model_name,frequency);

  if (!cpuinfo.is_open()) {
	std::cout << "Can not open /proc/cpuinfo" << std::endl;
	throw std::runtime_error("Can not open /proc/cpuinfo");
  }

  while (getline(cpuinfo, line)) {
	std::stringstream ss(line);
	std::string key, value;
	if (line.find("processor") == 0) {
	  if (!cpu_descr.model().empty()) {
		cpuInfoList_.push_back(cpu_descr);
	  }
	  cpu_descr = CpuDescr("","","","");
	}
	if (line.find("model name") == 0) {
	  cpu_descr.set_model(line.substr(line.find(':') + 1, line.length()));
	}
	if (line.find("processor") == 0) {
	  cpu_descr.set_core_id(line.substr(line.find(':') + 1, line.length()));
	}
	if (line.find("cpu MHz") == 0) {
	  cpu_descr.set_frequency(line.substr(line.find(':') + 1, line.length()));
	}

	if(line.find("vendor_id")==0){
	  cpu_descr.set_vendor(line.substr(line.find(':') + 1, line.length()));
	}
  }
  if (!cpu_descr.model().empty()) {
	cpuInfoList_.push_back(cpu_descr);
  }

}

std::string CpuDescr::core_id() const {
  return core_id_;
}
std::string CpuDescr::vendor() const {
  return vendor_;
}
std::string CpuDescr::model() const {
  return model_;
}
std::string CpuDescr::frequency() const {
  return frequency_;
}
CpuDescr::CpuDescr(std::string_view core_id,
				   std::string_view vendor,
				   std::string_view model,
				   std::string_view frequency) noexcept
	:
	core_id_(core_id),
	vendor_(vendor),
	model_(model),
	frequency_(frequency) {}

void CpuDescr::set_core_id(const std::string& core_id) {
  core_id_ = core_id;
}
void CpuDescr::set_vendor(const std::string& vendor) {
  vendor_ = vendor;

}
void CpuDescr::set_model(const std::string& model) {
  model_ = model;

}
void CpuDescr::set_frequency(const std::string& frequency) {
  frequency_ = frequency;

}

