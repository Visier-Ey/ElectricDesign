#ifndef __LAUNCH_STATION_H
#define __LAUNCH_STATION_H

// 归一化到[-1, 1]区间
float normalize(float value, float min, float max) {
    return (value - min) / (max - min) * 2 - 1;
}


#endif