namespace sensorMeas
{

    struct AccMeas
    {
        float x_dot_dot{};
        float y_dot_dot{};
        float z_dot_dot{};
    };
    struct GyroMeas
    {
        float psi_dot_x{};
        float psi_dot_y{};
        float psi_dot_z{};
    };
    struct MagMeas
    {
        float B_x{};
        float B_y{};
        float B_z{};
    };
    struct GPSMeas
    {
        float x{};
        float y{};
        float z{};
    };

}
