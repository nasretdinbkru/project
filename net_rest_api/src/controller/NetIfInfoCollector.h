#ifndef NETIFINFOCOLLECTOR_H
#define NETIFINFOCOLLECTOR_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
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
  //IfDescr(const IfDescr&) = delete;
  IfDescr(const std::string_view ifname,
          const std::string_view ipv4,
          const std::string_view brd,
          const uint8_t prefix,
          const std::string_view mac_addr);

  std::string ipv4() const;
  std::string ifname() const;
  std::string broasdcast() const;
  uint8_t prefix() const;

  std::string mac_aadr();

private:
  const std::string _if_name;
  const std::string _ipv4;
  const std::string _brd;
  const uint8_t _prefix;
  const std::string _mac_addr;

};


class InfoCollertor{
public:
  InfoCollertor(const InfoCollertor&) = delete;
  InfoCollertor& operator=(const InfoCollertor&) = delete;
  InfoCollertor();
  ~InfoCollertor();
  std::list<IfDescr> ifDescrList();
private:
  const uint16_t BUFLEN = 4096;
  int fd = 0;
  size_t len = 0;
  struct sockaddr_nl sa = { 0, 0, 0, 0 };
  char buf[4096];
  std::list<IfDescr> _if_descr_list = {};

  size_t get_ip( int domain);
  size_t get_msg(int fd, struct sockaddr_nl *sa, void *buf, size_t len);
  uint32_t parse_nl_msg(void *buf, size_t len);
  IfDescr parse_ifa_msg(struct ifaddrmsg *ifa, void *buf, size_t len);
  char* ntop(int domain, void *buf);
};



#endif // NETIFINFOCOLLECTOR_H
