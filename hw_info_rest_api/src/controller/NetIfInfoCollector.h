#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <iostream>
#include <string_view>
#include <cstring>
#include <list>




class IfDescr{
public:
  IfDescr(std::string_view ifname,
          std::string_view ipv4,
          std::string_view brd,
          uint8_t prefix,
          std::string_view mac_addr) noexcept;
  IfDescr() = delete;
  virtual ~IfDescr() = default;
  IfDescr& operator=(const IfDescr& other) = delete;


  [[nodiscard]] std::string ipv4() const;
  [[nodiscard]] std::string ifname() const;
  [[nodiscard]] std::string broasdcast() const;
  [[nodiscard]] uint8_t prefix() const;

  std::string mac_aadr();

private:
  const std::string if_name_;
  const std::string ipv4_;
  const std::string brd_;
  const uint8_t prefix_;
  const std::string mac_addr_;

};


class NetInfoCollertor{
public:
  NetInfoCollertor();
  NetInfoCollertor(const NetInfoCollertor&) = delete;
  NetInfoCollertor& operator=(const NetInfoCollertor&) = delete;
  NetInfoCollertor&& operator=(const NetInfoCollertor&&) = delete;
  virtual ~NetInfoCollertor();

  std::list<IfDescr> ifDescrList();
private:
  const uint16_t BUFLEN = 4096;
  int fd = 0;
  size_t len = 0;
  struct sockaddr_nl sa = { 0, 0, 0, 0 };
  char buf[4096];
  std::list<IfDescr> _if_descr_list = {};

  size_t get_ip( int domain);
  static size_t get_msg(int fd_, struct sockaddr_nl *sa_, void *buf_, size_t len_);
  uint32_t parse_nl_msg(void *buf_, size_t len_);
  static IfDescr parse_ifa_msg(struct ifaddrmsg *ifa, void *buf_, size_t len_);
  static char* ntop(int domain, void *buf_);
};
