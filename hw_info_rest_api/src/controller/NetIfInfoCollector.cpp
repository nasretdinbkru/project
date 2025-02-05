#include "NetIfInfoCollector.h"
#include <sstream>
NetInfoCollertor::NetInfoCollertor(){
    // Create a socket with the AF_NETLINK domain

    fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (fd == -1){
        std::cout << "Can't open socket" << std::endl;
    }

    sa.nl_family = AF_NETLINK;
    len = get_ip(AF_INET); // To get ipv6, use AF_INET6 instead
    char buf[BUFLEN];
    uint32_t nl_msg_type;
    do {
        len = get_msg(fd, &sa, buf, BUFLEN);

        nl_msg_type = parse_nl_msg(buf, len);
    } while (nl_msg_type != NLMSG_DONE && nl_msg_type != NLMSG_ERROR);

}

NetInfoCollertor::~NetInfoCollertor(){
    close(fd);
}

std::list<IfDescr> NetInfoCollertor::ifDescrList(){
    return this->_if_descr_list;
}

size_t NetInfoCollertor::get_ip(int domain){

    // assemble the message according to the netlink protocol
    std::fill(buf, buf+4096, 0);
    struct nlmsghdr *nl;
    nl = reinterpret_cast<struct nlmsghdr*>(buf);
    //nl = (struct nlmsghdr*)buf;
    nl->nlmsg_len = NLMSG_LENGTH(sizeof(struct ifaddrmsg));
    nl->nlmsg_type = RTM_GETADDR;
    nl->nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT;

    struct ifaddrmsg *ifa;
    ifa = reinterpret_cast<struct ifaddrmsg*>(NLMSG_DATA(nl));
    ifa->ifa_family = domain; // we only get ipv4 address here

    // prepare struct msghdr for sending.
    struct iovec iov = { nl, nl->nlmsg_len };
    struct msghdr msg = { &sa, sizeof(sa), &iov, 1, nullptr, 0, 0 };

    // send netlink message to kernel.
    ssize_t r = sendmsg(fd, &msg, 0);
    return (r < 0) ? -1 : 0;
}

size_t NetInfoCollertor::get_msg(int fd_, sockaddr_nl *sa_, void *buf_, size_t len_)
{
    struct iovec iov{};
    struct msghdr msg{};
    iov.iov_base = buf_;
    iov.iov_len = len_;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = sa_;
    msg.msg_namelen = sizeof(*sa_);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    return recvmsg(fd_, &msg, 0);
}

uint32_t NetInfoCollertor::parse_nl_msg(void *buf_, size_t len_)
{
    struct nlmsghdr *nl = nullptr;

    for (nl = reinterpret_cast<struct nlmsghdr*>(buf_);
         NLMSG_OK(nl, (uint32_t)len_) && nl->nlmsg_type != NLMSG_DONE;
         nl = NLMSG_NEXT(nl, len_)){
        if (nl->nlmsg_type == NLMSG_ERROR) {
            printf("error");
            return 1;
        }

        if (nl->nlmsg_type == RTM_NEWADDR) {
            struct ifaddrmsg *ifa;
            ifa = reinterpret_cast<struct ifaddrmsg*>(NLMSG_DATA(nl));
            _if_descr_list.push_back(parse_ifa_msg(ifa, IFA_RTA(ifa), IFA_PAYLOAD(nl)));
            continue;
        }
    }
    return nl->nlmsg_type;
}

IfDescr NetInfoCollertor::parse_ifa_msg(ifaddrmsg *ifa, void *buf_, size_t len_){
    char ifname[IF_NAMESIZE];
    std::string_view address;
    std::string_view broadcast;
    std::string_view mac_addr;


    std::string_view ifname_s(if_indextoname(ifa->ifa_index, ifname));
    uint8_t prefix(ifa->ifa_prefixlen);

    struct rtattr *rta = nullptr;
    int fa = ifa->ifa_family;
    for (rta = reinterpret_cast<struct rtattr*>(buf_); RTA_OK(rta, len_); rta = RTA_NEXT(rta, len_)){
        if (rta->rta_type == IFA_ADDRESS) {
            address = std::string(ntop(fa, RTA_DATA(rta)));
        }
        //int* tmp = reinterpret_cast<int*>(rta->rta_type);

        if(rta->rta_type == IFLA_ADDRESS)
        {
            char addr_buf[64];
            auto* c = reinterpret_cast<unsigned char*>(RTA_DATA(rta));

            snprintf(addr_buf, 64, "%02x:%02x:%02x:%02x:%02x:%02x",
                     c[0], c[1], c[2], c[3], c[4], c[5]);
            mac_addr = addr_buf;
        }

        if (rta->rta_type == IFA_BROADCAST) {
            broadcast = std::string(ntop(fa, RTA_DATA(rta)));
        }
    }
    return {ifname_s, address, broadcast, prefix, mac_addr};
}

char *NetInfoCollertor::ntop(int domain, void *buf_)
{
    /*
         * this function is not thread safe
         */
    static char ip[INET_ADDRSTRLEN];
    inet_ntop(domain, buf_, ip, INET_ADDRSTRLEN);
    return ip;
}

IfDescr::IfDescr(const std::string_view ifname, const std::string_view ipv4,
				 const std::string_view brd, const uint8_t prefix, const std::string_view mac_addr)
    :
	if_name_(ifname),
	ipv4_(ipv4),
	brd_(brd),
	prefix_(prefix),
	mac_addr_(mac_addr)

{}

std::string IfDescr::ipv4() const{
    return ipv4_;
}

std::string IfDescr::ifname() const{
    return if_name_;
}

std::string IfDescr::broasdcast() const{
    return brd_;
}


uint8_t IfDescr::prefix() const
{
    return prefix_;
}


std::string IfDescr::mac_aadr(){
    return mac_addr_;
}
