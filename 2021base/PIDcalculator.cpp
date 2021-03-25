/*
    PIDcalculator.cpp

    Copyright © 2021 Wataru Taniguchi. All rights reserved.
*/
#include "appusr.hpp"

PIDcalculator::PIDcalculator(double p, double i, double d, int16_t t, int16_t min, int16_t max) {
    kp = p;
    ki = i;
    kd = d;
    diff[1] = INT16_MAX; // initialize diff[1]
    deltaT = t;
    minimum = min;
    maximum = max;
    traceCnt = 0;
}

PIDcalculator::~PIDcalculator() {};

int16_t PIDcalculator::math_limit(int16_t input, int16_t min, int16_t max) {
    if (input < min) {
        return min;
    } else if (input > max) {
        return max;
    }
    return input;
}

int16_t PIDcalculator::compute(int16_t sensor, int16_t target) {
    double p, i, d;
    
    if ( diff[1] == INT16_MAX ) {
	    diff[0] = diff[1] = sensor - target;
    } else {
        diff[0] = diff[1];
        diff[1] = sensor - target;
    }
    integral += (double)(diff[0] + diff[1]) / 2.0 * deltaT / 1000.0;
    
    p = kp * diff[1];
    i = ki * integral;
    d = kd * (diff[1] - diff[0]) * 1000.0 / deltaT;
    /*
    if (++traceCnt * PERIOD_NAV_TSK >= PERIOD_TRACE_MSG) {
        traceCnt = 0;
        char buf[128];
        snprintf(buf, sizeof(buf), "p = %lf, i = %lf, d = %lf", p, i, d);
        _debug(syslog(LOG_NOTICE, "%08u, PIDcalculator::compute(): sensor = %d, target = %d, d0 = %d, d1 = %d +", clock->now(), sensor, target, diff[0], diff[1]));
        _debug(syslog(LOG_NOTICE, "%08u, PIDcalculator::compute(): sensor = %d, target = %d, %s", clock->now(), sensor, target, buf));    }
    */
    return math_limit(p + i + d, minimum, maximum);
}