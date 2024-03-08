#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
// 8851 Daten sind da drin vorhanden
// In welcher Einheit sind die Sekunden angegeben? Laut Abgabe in Microsekunden
// alle 2 sekunden kommt ein GPS rein

const int DATA_ROWS = 8851;

struct SensorData
{
    float x{};
    float y{};
    float z{};
};

struct IMU
{
    int port{};
    std::vector<float> timeData{std::vector<float>(DATA_ROWS)};
    std::vector<SensorData> accData{std::vector<SensorData>(DATA_ROWS)};
    std::vector<SensorData> gyroData{std::vector<SensorData>(DATA_ROWS)};
    std::vector<SensorData> magData{std::vector<SensorData>(DATA_ROWS)};
} imu_1, imu_2, imu_3, imu_4;

int main()
{

    // read in of datafiles with the coloum structure:
    // Time [us]	ACC_X [mg]	ACC_Y [mg]	ACC_Z [mg]	GYRO_X [dps]	GYRO_Y [dps]	GYRO_Z [dps]	MAG_X [uT]	MAG_Y [uT]	MAG_Z [uT]
    std::string data_IMU_path{"/workspaces/dev_container_kalman_filter_offline/old_data_from_sd/IMU_"};

    imu_1.port = 0;
    imu_2.port = 1;
    imu_3.port = 6;
    imu_4.port = 7;

    IMU imus[4] = {imu_1, imu_2, imu_3, imu_4};

    int coloumn = 0; // Index for the array of values
    int row = 0;
    size_t pos = 0; // position of the delimiter in string
    std::string data{};
    std::string delimiter{};
    std::string path_ending{};

    for (IMU &imu : imus)
    {
        std::stringstream filepath{};
        filepath << data_IMU_path << imu.port << "/IMU_" << imu.port << "_data.txt";
        std::cout << filepath.str();
        std::ifstream data_IMU{filepath.str()};

        if (!data_IMU.is_open())
        {
            std::cerr << "Fehler beim Öffnen der Datei!" << std::endl;
            return 1; // Rückgabe eines Fehlercodes
        }

        for (std::string values; std::getline(data_IMU, values) && row < DATA_ROWS; row++)
        {
            coloumn = 0;
            while (coloumn < 10)
            {
                if (coloumn != 9)
                {
                    delimiter = "\t";
                }
                else
                {
                    delimiter = "\r";
                }
                pos = values.find(delimiter);

                data = values.substr(0, pos);
                float number = std::stof(data);
                if (coloumn == 0)
                {
                    imu.timeData[row] = std::stof(data);
                }
                if (coloumn == 1)
                {
                    imu.accData[row].x = std::stof(data);
                }
                if (coloumn == 2)
                {
                    imu.accData[row].y = std::stof(data);
                }
                if (coloumn == 3)
                {
                    imu.accData[row].z = std::stof(data);
                }
                if (coloumn == 4)
                {
                    imu.gyroData[row].x = std::stof(data) * M_PI / 180.0F;
                }
                if (coloumn == 5)
                {
                    imu.gyroData[row].y = std::stof(data) * M_PI / 180.0F;
                }
                if (coloumn == 6)
                {
                    imu.gyroData[row].z = std::stof(data) * M_PI / 180.0F;
                }
                if (coloumn == 7)
                {
                    imu.magData[row].x = std::stof(data);
                }
                if (coloumn == 8)
                {
                    imu.magData[row].y = std::stof(data);
                }
                if (coloumn == 9)
                {
                    imu.magData[row].z = std::stof(data);
                }
                values.erase(0, pos + delimiter.length());
                coloumn++;
            }
        }
    }
    return 0;
}
