#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include <iostream>
#include <string>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "NetIfInfoCollector.h"
#include "MemInfoCollector.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */


class AppController : public oatpp::web::server::api::ApiController {
public:
    /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
    explicit AppController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
        : oatpp::web::server::api::ApiController(apiContentMappers)
    {}
public:

    ENDPOINT("GET", "/", root) {
        auto dto = MyDto::createShared();
        dto->statusCode = 200;
        dto->message = "API server";

        OATPP_LOGi("API", "status code {}", dto->statusCode);
        return createDtoResponse(Status::CODE_200, dto);
    }


    ENDPOINT("GET", "/ipv4", ipv4){
        oatpp::List<oatpp::Object<IPv4Info>> ifInfoList({});
        InfoCollertor ic;
        for (auto ic_item: ic.ifDescrList()){
            auto if_info_dto = IPv4Info::createShared();
            if_info_dto->if_name = ic_item.ifname();
            if_info_dto->ipv4add = ic_item.ipv4();
            if_info_dto->broadcat = ic_item.broasdcast();
            if_info_dto->prefix = ic_item.prefix();
            if_info_dto->mac_addr = ic_item.mac_aadr();
            ifInfoList->push_back(if_info_dto);

        }
        return createDtoResponse(Status::CODE_200, ifInfoList);
    }

    ENDPOINT("GET", "/ipv6", ipv6){
        oatpp::List<oatpp::Object<IPv6Info>> ifInfoList({});
        struct ifaddrs * ifAddrStruct=nullptr;
        struct ifaddrs * ifa=nullptr;
        void * tmpV6AddrPtr=nullptr;
        getifaddrs(&ifAddrStruct);

        for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) {
            if (!ifa->ifa_addr) {
                continue;
            }

            if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
                // is a valid IP6 Address
                tmpV6AddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
                char addressBuffer[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmpV6AddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                auto if_info_dto = IPv6Info::createShared();

                if_info_dto->if_name = std::string(ifa->ifa_name);
                if_info_dto->ipv6add = std::string(addressBuffer);
                ifInfoList->push_back(if_info_dto);
            }
        }
        if (ifAddrStruct!=nullptr) freeifaddrs(ifAddrStruct);
        return createDtoResponse(Status::CODE_200, ifInfoList);
    }
    ENDPOINT("GET", "/meminfo", meminfo){
        oatpp::Object<MemInfo> memInfo({});

		MemInfoCollector mem_info_collector({});
		MemDescr memDescr(mem_info_collector.memTotal, mem_info_collector.memFree,
						   mem_info_collector.memAvailable, mem_info_collector.swapTotal, mem_info_collector.swapTotal);

		auto mem_info_dto = MemInfo::createShared();
		mem_info_dto->memFree = memDescr.memTotal();
		mem_info_dto->memTotal = memDescr.memTotal();
		mem_info_dto->memAvailable = memDescr.memAvailable();
		mem_info_dto->swapTotal = memDescr.swapTotal();
		mem_info_dto->swapFree = memDescr.swapFree();
        return createDtoResponse(Status::CODE_200, mem_info_dto);
    }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
