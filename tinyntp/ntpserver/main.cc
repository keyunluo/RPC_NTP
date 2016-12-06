#include <iostream>
#include <ctime>
#include <string>
#include <thread>
#include "server/server.h"


int main(int argc, char *argv[]) {

    int port, verified_id;
    std::string ip ;
    std::map<std::string, std::string> m_mapConfig;
    bool read_success = tinyrpc::ReadConfig("server.conf", m_mapConfig);
    if (!read_success){
        ip = "0.0.0.0";
        port = 20160;
        verified_id = 2016;
    } else{
        ip = m_mapConfig["ip"];
        port = std::stoi(m_mapConfig["port"]);
        verified_id = std::stoi(m_mapConfig["verified_id"]);
    }

    tinyrpc::server srv(ip, port);

    srv.bind("gettime", [=](int verify_id){
        if (verify_id % verified_id != 0){
            return std::string();
        }

        time_t current_time;
        struct tm *ret_time;
        time(&current_time);
        ret_time = localtime(&current_time);

        char* result = asctime(ret_time);
        std::string time(result);
		std::cout<< "Current Time:" << result << std::endl;

        return time.substr(11, 8);
    });

    //srv.run();
    srv.async_run(std::thread::hardware_concurrency());
    std::cin.ignore();
    srv.suppress_exceptions(true);
    return 0;
}
