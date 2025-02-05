//
// Created by ray on 05.02.2025.
//

#ifndef HW_INFO_REST_API_SRC_CONTROLLER_HDDINFOCOLLECTOR_H_
#define HW_INFO_REST_API_SRC_CONTROLLER_HDDINFOCOLLECTOR_H_
#include <iostream>
#include <utility>

class HddDescr {

 public:

  HddDescr& operator=(const HddDescr&) = delete;
  HddDescr() = default;
  HddDescr(std::string device_name,
		   std::string model,
		   std::string serial,
		   std::string disk_size);
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
  HddInfoCollector& operator=(const HddInfoCollector&) = delete;
  HddInfoCollector();
  static HddDescr collect_disk_info(struct udev_device* dev);
  std::vector<HddDescr> hdd_list();
 private:
  std::vector<HddDescr> hdd_list_;

};

#endif //HW_INFO_REST_API_SRC_CONTROLLER_HDDINFOCOLLECTOR_H_
