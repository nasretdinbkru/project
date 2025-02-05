//
// Created by ray on 05.02.2025.
//
#include <iostream>
#include <libudev.h>
#include <cstring>
#include <cmath>
#include <utility>
#include <vector>
#include "HddInfoCollector.h"

//struct DiskInfo {
//  std::string device_name;
//  std::string model;
//  std::string serial;
//  std::string disk_size;
//};

//DiskInfo collect_disk_info(struct udev_device* dev) {
//  const char* model = udev_device_get_property_value(dev, "ID_MODEL");
//  const char* serial = udev_device_get_property_value(dev, "ID_SERIAL_SHORT");
//  const char* devnode = udev_device_get_devnode(dev);
//  const char* size_m = udev_device_get_sysattr_value(dev, "size");
//  auto qqq = udev_device_get_sysattr_value(dev, "queue/logical_block_size");
//
//  long long size_in_gb = 0;
//  DiskInfo disk_info;
//  if (size_m) {
//	long long size_in_blocks = std::atoll(size_m);
////	size_in_gb = std::roundl(size_in_blocks / (2024.0 * 965.0) / 2);
//	size_in_gb = std::roundl(size_in_blocks / (2024.0 * 1024.0) / 1.886);
//  }
//
//  if (model && serial && devnode) {
//	std::cout << "Device: " << devnode << std::endl;
//	std::cout << "Model: " << model << std::endl;
//	std::cout << "Serial Number: " << serial << std::endl;
//	std::cout << "Size: " << size_in_gb << " GB" << std::endl << std::endl;
//	disk_info.device_name = devnode;
//	disk_info.model = model;
//	disk_info.serial = serial;
//	disk_info.disk_size = std::to_string(size_in_gb);
//  }
//  return disk_info;
//}
//
//int main() {
//  // Инициализируем udev
//  struct udev* udev = udev_new();
//  if (!udev) {
//	std::cerr << "Unable to create udev context" << std::endl;
//	return 1;
//  }
//
//  // Ищем все устройства с типом "disk"
//  struct udev_enumerate* enumerate = udev_enumerate_new(udev);
//  udev_enumerate_add_match_subsystem(enumerate, "block");
//  udev_enumerate_scan_devices(enumerate);
//
//  struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
//  struct udev_list_entry* entry;
//  std::vector<DiskInfo> disks;
//
//  udev_list_entry_foreach(entry, devices) {
//	const char* path = udev_list_entry_get_name(entry);
//	struct udev_device* dev = udev_device_new_from_syspath(udev, path);
//
//	if (dev) {
//	  // Проверяем, что устройство — это жесткий диск (например, /dev/sda, /dev/nvme0n1 и т.д.)
//	  const char* devtype = udev_device_get_devtype(dev);
//
//	  std::string sysname(udev_device_get_sysname(dev));
//	  if (devtype && strcmp(devtype, "disk") == 0 && sysname.find("sd") == 0) {
//		disks.push_back(collect_disk_info(dev));
//		//collect_disk_info(dev);
//	  }
//	  udev_device_unref(dev);
//	}
//  }
//
//  // Освобождаем ресурсы
//  udev_enumerate_unref(enumerate);
//  udev_unref(udev);
//
//  return 0;
//}
HddDescr::HddDescr(std::string  device_name,
				   std::string  model,
				   std::string  serial,
				   std::string  disk_size)
	:
	device_name_(std::move(device_name)),
	model_(std::move(model)),
	serial_(std::move(serial)),
	disk_size_(std::move(disk_size)) {}
//std::string HddDescr::device_name() const {
//  return device_name_;
//}
std::string HddDescr::model() const {
  return model_;
}
std::string HddDescr::serial() const {
  return serial_;
}
std::string HddDescr::disk_size() const {
  return disk_size_;
}

HddInfoCollector::HddInfoCollector() {
  struct udev* udev = udev_new();
  if (!udev) {
	std::cerr << "Unable to create udev context" << std::endl;
	throw;
  }

  // Ищем все устройства с типом "disk"
  struct udev_enumerate* enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(enumerate, "block");
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry* entry;
  //std::vector<DiskInfo> disks;

  udev_list_entry_foreach(entry, devices) {
	const char* path = udev_list_entry_get_name(entry);
	struct udev_device* dev = udev_device_new_from_syspath(udev, path);

	if (dev) {
	  // Проверяем, что устройство — это жесткий диск (например, /dev/sda, /dev/nvme0n1 и т.д.)
	  const char* devtype = udev_device_get_devtype(dev);

	  std::string sysname(udev_device_get_sysname(dev));
	  if (devtype && strcmp(devtype, "disk") == 0 && sysname.find("sd") == 0) {
		hdd_list_.push_back(collect_disk_info(dev));
	  }
	  udev_device_unref(dev);
	}
  }
  // Освобождаем ресурсы
  udev_enumerate_unref(enumerate);
  udev_unref(udev);
}

HddDescr HddInfoCollector::collect_disk_info(struct udev_device* dev) {
  const char* model = udev_device_get_property_value(dev, "ID_MODEL");
  const char* serial = udev_device_get_property_value(dev, "ID_SERIAL_SHORT");
  const char* devnode = udev_device_get_devnode(dev);
  const char* size_m = udev_device_get_sysattr_value(dev, "size");
  long long size_in_gb = 0;

  if (size_m) {
	long long size_in_blocks = std::atoll(size_m);
	size_in_gb = std::roundl(size_in_blocks / (2024.0 * 1024.0) / 1.886);
  }

  if (model && serial && devnode) {

	HddDescr disk_info(devnode, model, serial, std::to_string(size_in_gb));
	return disk_info;
  }
  return {};
}
std::vector<HddDescr> HddInfoCollector::hdd_list() {
  return hdd_list_;
}
std::string HddDescr::device_name() const {
  return device_name_;
}
