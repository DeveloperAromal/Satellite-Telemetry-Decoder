#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <thread>
#include <chrono>

#pragma pack(push, 1)

struct TelemetryPacket{
    uint32_t timestamp;
    float voltage;
    float altitude;
    char signal[4];
};

#pragma pack(pop)

int main () {
    std::ifstream file("D:/ISRO_Projects/satellite_telemetry/data/telemetry.bin", std::ios::binary);

    if(!file){
        std::cerr << "No file found";
        return 1;
    }

    file.seekg(0, std::ios::beg);

    TelemetryPacket packet;

    while (true){
        if(file.read(reinterpret_cast<char*>(&packet), sizeof(packet))){
            std::cout << "📡 Listening for telemetry packets...\n";
            std::cout << " | Time: " << packet.timestamp
                  << " | Voltage: " << std::fixed << std::setprecision(2) << packet.voltage
                  << " | Altitude: " << packet.altitude
                  << " | Signal: " << std::string(packet.signal, 4)
                  << "\n";
        }else{
            file.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return 0;
}
