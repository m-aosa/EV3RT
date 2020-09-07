//
//  aflac_common.hpp
//  aflac2020
//
//  Copyright © 2019 Ahiruchan Koubou. All rights reserved.
//

#ifndef aflac_common_hpp
#define aflac_common_hpp

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/**
 * 左コース/右コース向けの設定を定義します
 * デフォルトは左コース(ラインの右エッジをトレース)です
 */
#if defined(MAKE_RIGHT)
    static const int _LEFT = 0;
    #define _EDGE -1
#else
    static const int _LEFT = 1;
    #define _EDGE 1
#endif

//#include <cinttypes>
#include <cmath>
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Steering.h"
#include "Clock.h"
using namespace ev3api;
#include "utility.hpp"

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define LIGHT_WHITE          60  /* 白色の光センサ値 */
#define LIGHT_BLACK           3  /* 黒色の光センサ値 */
#define GS_LOST              90  // threshold to determine "line lost"
#define FINAL_APPROACH_LEN  100  // final approch length in milimater
#define ANG_V_TILT           50  // threshold to determine "tilt"
#define SONAR_ALERT_DISTANCE 10  /* 超音波センサによる障害物検知距離[cm] */
#define TAIL_ANGLE_STAND_UP  85  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define P_GAIN             2.5F  /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60  /* 完全停止用モータ制御PWM絶対最大値 */

#define TIRE_DIAMETER    100.0F  // diameter of tire in milimater
#define WHEEL_TREAD      150.0F  // distance between the right and left wheels
//#define P_CONST           0.38D  // PID constants determined by Ultimate Gain method
//#define I_CONST           0.06D
//#define D_CONST          0.027D
#define P_CONST           0.46D  // PID constants determined by Ultimate Gain method
#define I_CONST     0.00000013D
#define D_CONST          0.075D
#define SPEED_NORM           45
#define TURN_MIN            -16  // minimum value PID calculator returns
#define TURN_MAX             16  // maximum value PID calculator returns
#define GS_TARGET            45

#define M_2PI    (2.0 * M_PI)

//#define DEVICE_NAME     "ET0"  /* Bluetooth名 hrp2/target/ev3.h BLUETOOTH_LOCAL_NAMEで設定 */
//#define PASS_KEY        "1234" /* パスキー    hrp2/target/ev3.h BLUETOOTH_PIN_CODEで設定 */
#define CMD_START_R     'R' // R-mode start command
#define CMD_START_r     'r' // R-mode start command
#define CMD_START_L     'L' // L-mode start command
#define CMD_START_l     'l' // L-mode start command
#define CMD_STOP_S      'S'
#define CMD_STOP_s      's'

// machine state
#define ST_start    0
#define ST_tracing_L    1
#define ST_crimbing     2
#define ST_tracing_R    3
#define ST_dancing      4
#define ST_stopping_L   5
#define ST_stopping_R   6
#define ST_ending      7

#define ST_NAME_LEN     20  // maximum number of characters for a machine state name
const char stateName[][ST_NAME_LEN] = {
    "ST_start",
    "ST_tracing_L",
    "ST_crimbing",
    "ST_tracing_R",
    "ST_dancing",
    "ST_stopping_L",
    "ST_stopping_R",
    "ST_ending"
};

// event
#define EVT_cmdStart_L      0
#define EVT_cmdStart_R      1
#define EVT_touch_On        2
#define EVT_touch_Off       3
#define EVT_sonar_On        4
#define EVT_sonar_Off       5
#define EVT_backButton_On   6
#define EVT_backButton_Off  7
#define EVT_bk2bl           8
#define EVT_bl2bk           9
#define EVT_cmdDance        10
#define EVT_cmdCrimb        11
#define EVT_cmdStop         12
#define EVT_line_lost       13
#define EVT_line_found      14
#define EVT_dist_reached    15
#define EVT_tilt            16

#define EVT_NAME_LEN        20  // maximum number of characters for an event name
const char eventName[][EVT_NAME_LEN] = {
    "EVT_cmdStart_L",
    "EVT_cmdStart_R",
    "EVT_touch_On",
    "EVT_touch_Off",
    "EVT_sonar_On",
    "EVT_sonar_Off",
    "EVT_backButton_On",
    "EVT_backButton_Off",
    "EVT_bk2bl",
    "EVT_bl2bk",
    "EVT_cmdDance",
    "EVT_cmdCrimb",
    "EVT_cmdStop",
    "EVT_line_lost",
    "EVT_line_found",
    "EVT_dist_reached",
    "EVT_tilt"
};

// global variables
extern rgb_raw_t g_rgb;
extern hsv_raw_t g_hsv;
extern int16_t g_grayScale, g_grayScaleBlueless;
extern int16_t g_angle, g_anglerVelocity;

extern Clock*       clock;
extern uint8_t      state;

#endif /* aflac_common_hpp */