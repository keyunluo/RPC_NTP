#include <QApplication>
#include "DigitalClock.h"

int main(int argc, char* argv[]) {
    int port, verify_id;
    std::string ip ;
    std::map<std::string, std::string> m_mapConfig;
    bool read_success = tinyrpc::ReadConfig("client.conf", m_mapConfig);
    if (!read_success){
        ip = "127.0.0.1";
        port = 20160;
        verify_id = 2016;
    } else{
        ip = m_mapConfig["ip"];
        port = std::stoi(m_mapConfig["port"]);
        verify_id = std::stoi(m_mapConfig["verify_id"]);
    }

    QApplication app(argc, argv);
    DigitalClock clock(ip, port, verify_id);

    clock.show();

    return app.exec();

}
