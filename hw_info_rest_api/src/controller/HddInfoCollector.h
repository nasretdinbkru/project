//
// Created by ray on 05.02.2025.
//

#ifndef HW_INFO_REST_API_SRC_CONTROLLER_HDDINFOCOLLECTOR_H_
#define HW_INFO_REST_API_SRC_CONTROLLER_HDDINFOCOLLECTOR_H_
#include <iostream>
#include <utility>

class HddDescr {
 public:
  HddDescr() = default;
  HddDescr(const std::string& device_name,
		   const std::string& model,
		   const std::string& serial,
		   const std::string& disk_size);
  [[nodiscard]] std::string device_name() const;
  [[nodiscard]] std::string model() const;
  [[nodiscard]] std::string serial() const;
  [[nodiscard]] std::string disk_size() const;
 private:
  std::string device_name_;
  std::string model_;
  std::string serial_;
  std::string disk_size_;

};

class HddInfoCollector {
 public:
  HddInfoCollector();
  static HddDescr collect_disk_info(struct udev_device* dev);
  std::vector<HddDescr> hdd_list();
 private:
  std::vector<HddDescr> hdd_list_;

};

#endif //HW_INFO_REST_API_SRC_CONTROLLER_HDDINFOCOLLECTOR_H_
