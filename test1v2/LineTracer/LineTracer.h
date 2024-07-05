#pragma once

#include <opencv2/opencv.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/* 下記の項目は各ロボットに合わせて変えること */


/* カラーセンサの輝度設定 */
constexpr int WHITE_BRIGHTNESS = 180;
constexpr int BLACK_BRIGHTNESS = 10;

/*カメラの閾値設定*/
constexpr int THRESHOLDVALUE = 50;
constexpr int MAXBINARYVALUE = 255;

/*カメラのトリミング*/
constexpr int TRIMY = 400;
constexpr int TRIMH = 30;

/*ブロックエリアの設定*/
constexpr int LB_X1 = B_W * 7;
constexpr int LB_X2 = B_W * 6;
constexpr int LB_X3 = B_W * 5;
constexpr int LB_X4 = B_W * 4;
constexpr int LB_X5 = B_W * 3;
constexpr int LB_X6 = B_W * 2;
constexpr int LB_X7 = B_W * 1;
constexpr int LB_X8 = 0;

constexpr int RB_X1 = B_W * 8;
constexpr int RB_X2 = B_W * 9;
constexpr int RB_X3 = B_W * 10;
constexpr int RB_X4 = B_W * 11;
constexpr int RB_X5 = B_W * 12;
constexpr int RB_X6 = B_W * 13;
constexpr int RB_X7 = B_W * 14;
constexpr int RB_X8 = B_W * 15;
constexpr int B_W = 15;
constexpr int ALLB_Y1 = 0;
constexpr int ALLB_Y2 = TRIMH;

/* ステアリング操舵量の係数 */
constexpr float STEERING_COEF = 0.2F;

/* 走行基準スピード */
constexpr int BASE_SPEED = 40;

/* ライントレースエッジ切り替え */
constexpr int LEFT_EDGE = -1;
constexpr int RIGHT_EDGE = 1;

#ifdef __cplusplus
}
#endif

const int XLPoint[8] = {
    LB_X1, LB_X2, LB_X3, LB_X4, LB_X5, LB_X6, LB_X7, LB_X8
};
const int XRPoint[8] = {
    RB_X1, RB_X2, RB_X3, RB_X4, RB_X5, RB_X6, RB_X7, RB_X8
};