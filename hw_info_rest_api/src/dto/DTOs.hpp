#pragma once
#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MyDto : public oatpp::DTO {
  
  DTO_INIT(MyDto, DTO)
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
  
};

class IPv4Info : public oatpp::DTO {
    DTO_INIT(IPv4Info, DTO);
    DTO_FIELD(String, if_name);
    DTO_FIELD(String, ipv4add);
    DTO_FIELD(String, broadcat);
    DTO_FIELD(Int8, prefix);
    DTO_FIELD(String, mac_addr);
};

class IfIPv4InfoList: public oatpp::DTO{
    DTO_INIT(IfIPv4InfoList, DTO);
    DTO_FIELD(Vector<Object<IPv4Info>>, ifinfolist);
};


class IPv6Info : public oatpp::DTO {
    DTO_INIT(IPv6Info, DTO);
    DTO_FIELD(String, if_name);
    DTO_FIELD(String, ipv6add);
};


class IfIPv6InfoList: public oatpp::DTO{
    DTO_INIT(IfIPv4InfoList, DTO);
    DTO_FIELD(Vector<Object<IPv6Info>>, ifinfolist);
};


class MemInfo: public oatpp::DTO{
    DTO_INIT(MemInfo, DTO);
    DTO_FIELD(String, memTotal);
    DTO_FIELD(String, memFree);
    DTO_FIELD(String, memAvailable);
    DTO_FIELD(String, swapTotal);
    DTO_FIELD(String, swapFree);
};


class HddInfo: public oatpp::DTO {
  DTO_INIT(HddInfo, DTO);
  DTO_FIELD(String, deviceName);
  DTO_FIELD(String, model);
  DTO_FIELD(String, serial);
  DTO_FIELD(String, diskSize);

};

class HddInfoList: public oatpp::DTO {
  DTO_INIT(HddInfoList, DTO);
  DTO_FIELD(Vector<Object<HddInfo>>, hddInfolist);
};

class CpuInfo: public oatpp::DTO {
  DTO_INIT(CpuInfo, DTO);
  DTO_FIELD(String, model);
  DTO_FIELD(String, coreid);
  DTO_FIELD(String, frequency);
  DTO_FIELD(String, vendor);
};

class CpuInfoList: public oatpp::DTO {
  DTO_INIT(CpuInfoList, DTO);
  DTO_FIELD(Vector<Object<CpuInfo>>, cpuInfolist);
};

#include OATPP_CODEGEN_END(DTO)
