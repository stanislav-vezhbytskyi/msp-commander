#pragma once

#include <cstdint>

namespace MSP {
    namespace MessageID {
        // TX
        constexpr uint8_t IDENT = 100;
        constexpr uint8_t STATUS = 101;
        constexpr uint8_t RAW_IMU = 102;
        constexpr uint8_t SERVO = 103;
        constexpr uint8_t MOTOR = 104;
        constexpr uint8_t RC = 105;
        constexpr uint8_t RAW_GPS = 106;
        constexpr uint8_t COMP_GPS = 107;
        constexpr uint8_t ATTITUDE = 108;
        constexpr uint8_t ALTITUDE = 109;
        constexpr uint8_t ANALOG = 110;
        constexpr uint8_t RC_TUNING = 111;
        constexpr uint8_t PID = 112;
        constexpr uint8_t BOX = 113;
        constexpr uint8_t MISC = 114;
        constexpr uint8_t MOTOR_PINS = 115;
        constexpr uint8_t BOXNAMES = 116;
        constexpr uint8_t PIDNAMES = 117;
        constexpr uint8_t WP = 118;
        constexpr uint8_t BOXIDS = 119;
        constexpr uint8_t SERVO_CONF = 120;

        // RX
        constexpr uint8_t SET_RAW_RC = 200;
        constexpr uint8_t SET_RAW_GPS = 201;
        constexpr uint8_t SET_PID = 202;
        constexpr uint8_t SET_BOX = 203;
        constexpr uint8_t SET_RC_TUNING = 204;
        constexpr uint8_t ACC_CALIBRATION = 205;
        constexpr uint8_t MAG_CALIBRATION = 206;
        constexpr uint8_t SET_MISC = 207;
        constexpr uint8_t RESET_CONF = 208;
        constexpr uint8_t SET_WP = 209;
        constexpr uint8_t SELECT_SETTING = 210;
        constexpr uint8_t SET_HEAD = 211;
        constexpr uint8_t SET_SERVO_CONF = 212;
        constexpr uint8_t SET_MOTOR = 214;
        constexpr uint8_t BIND = 240;
        constexpr uint8_t EEPROM_WRITE = 250;

        // Unofficial protocol extensions
        constexpr uint8_t EXT_NAV_STATUS = 121;
        constexpr uint8_t EXT_NAV_CONFIG = 122;
        constexpr uint8_t EXT_FW_CONFIG = 123;
        constexpr uint8_t EXT_UID = 160;
        constexpr uint8_t EXT_GPSSVINFO = 164;
        constexpr uint8_t EXT_GPSDEBUGINFO = 166;
        constexpr uint8_t EXT_ACC_TRIM = 240; // WARNING: shadows MSP_BIND
        constexpr uint8_t EXT_SERVOMIX_CONF = 241;

        constexpr uint8_t EXT_SET_NAV_CONFIG = 215;
        constexpr uint8_t EXT_SET_FW_CONFIG = 216;
        constexpr uint8_t EXT_SET_ACC_TRIM = 239;
        constexpr uint8_t EXT_SET_SERVOMIX_CONF = 242;

        constexpr uint8_t EXT_DEBUGMSG = 253;
        constexpr uint8_t EXT_DEBUG = 254;
    }

    struct PID {
        uint8_t p, i, d;
    };

    struct GyroData {
        float x, y, z;
    };
}
