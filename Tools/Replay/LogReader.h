#include <VehicleType.h>
#include <DataFlashFileReader.h>
#include <LR_MsgHandler.h>

class LogReader : public DataFlashFileReader
{
public:
    LogReader(AP_AHRS &_ahrs, AP_InertialSensor &_ins, AP_Baro &_baro, Compass &_compass, AP_GPS &_gps, AP_Airspeed &_airspeed, DataFlash_Class &_dataflash);
    bool wait_type(const char *type);

    const Vector3f &get_attitude(void) const { return attitude; }
    const Vector3f &get_ahr2_attitude(void) const { return ahr2_attitude; }
    const Vector3f &get_inavpos(void) const { return inavpos; }
    const Vector3f &get_sim_attitude(void) const { return sim_attitude; }
    const float &get_relalt(void) const { return rel_altitude; }

    VehicleType::vehicle_type vehicle;

    bool set_parameter(const char *name, float value);

    void set_accel_mask(uint8_t mask) { accel_mask = mask; }
    void set_gyro_mask(uint8_t mask) { gyro_mask = mask; }
    void set_use_imt(bool _use_imt) { use_imt = _use_imt; }

    uint64_t last_timestamp_us(void) const { return last_timestamp_usec; }
    virtual bool handle_log_format_msg(const struct log_Format &f);
    virtual bool handle_msg(const struct log_Format &f, uint8_t *msg);

private:
    AP_AHRS &ahrs;
    AP_InertialSensor &ins;
    AP_Baro &baro;
    Compass &compass;
    AP_GPS &gps;
    AP_Airspeed &airspeed;
    DataFlash_Class &dataflash;

    uint8_t accel_mask;
    uint8_t gyro_mask;
    bool use_imt = true;

    uint32_t ground_alt_cm;

    class LR_MsgHandler *msgparser[LOGREADER_MAX_FORMATS];

    Vector3f attitude;
    Vector3f ahr2_attitude;
    Vector3f sim_attitude;
    Vector3f inavpos;
    float rel_altitude;
    uint64_t last_timestamp_usec;

    bool installed_vehicle_specific_parsers;
    void maybe_install_vehicle_specific_parsers();

    bool in_list(const char *type, const char *list[]);
};
