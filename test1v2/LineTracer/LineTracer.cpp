#include <opencv2/opencv.hpp>
#include "app.h"
#include "LineTracer.h"
#include <stdio.h>
#include <iostream>
#include <bitset>

/* 関数プロトタイプ宣言 */

struct PID {
    double Kp, Ki, Kd;
    double previous_error, integral;
};

double pid_control(PID &pid, double error);
static void Capture(void); 
static void motor_cntrol(int Lsensor_count , int Rsensor_count);

PID pid = {1, 0, 0, 0, 0}; 



/* ライントレースタスク(100msec周期で関数コールされる) */
void tracer_task(intptr_t unused) {
    Capture();

    /* タスク終了 */
    ext_tsk();
}

static void Capture(void){
    cv::VideoCapture camera(0);
    int retry_count = 0;
    int Lsensor_count = 0;
    int Rsensor_count = 0;
    const int max_retries = 5;
    if (!camera.isOpened()) {
        std::cerr << "Error: Camera could not be opened." << std::endl;
        return;
    }
    cv::Mat frame;
    while (retry_count < max_retries) {
        camera >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Frame is empty. Retrying..." << std::endl;
            retry_count++;
            continue;
        }
        break;
    }

    if (frame.empty()) {
        std::cerr << "Error: Frame is empty after maximum retries." << std::endl;
        return;
    }
    /*std::cout << "Cols: " << frame.cols << ", Rows: " << frame.rows << std::endl;*/
    frame = frame(cv::Rect(200, TRIMY, 440, TRIMH));
    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    cv::threshold(frame, frame, THRESHOLDVALUE, MAXBINARYVALUE, cv::THRESH_BINARY_INV);

    /*cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(frame, frame, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(frame, frame, cv::MORPH_CLOSE, kernel);*/

    for (int i = 0; i < 8; ++i) {
        if(cv::countNonZero(frame(cv::Rect(XLPoint[i], 0, B_W, ALLB_Y2))) >= 150 ){
            Lsensor_count++;
        }
    }
    for (int i = 0; i < 8; ++i) {
        if(cv::countNonZero(frame(cv::Rect(XRPoint[i], 0, B_W, ALLB_Y2))) >= 150 ){
            Rsensor_count++;
        }
    }
    std::cerr <<  "detectionFlags: " << Lsensor_count << ":" << Rsensor_count<< std::endl;
    motor_cntrol(Lsensor_count , Rsensor_count);
    camera.release();
    return;
}

double pid_control(PID &pid, double error) {
    pid.integral += error;
    double derivative = error - pid.previous_error;
    pid.previous_error = error;
    return pid.Kp * error + pid.Ki * pid.integral + pid.Kd * derivative;
}

/* 走行モータ制御 */
static void motor_cntrol(int Lsensor_count ,int Rsensor_count){
    int error = Lsensor_count - Rsensor_count;
    double control_signal = pid_control(pid, error);

    // 基準速度
    double base_speed = 95;

    // 左右のモータ速度の調整
    double left_motor_speed = base_speed - control_signal;
    double right_motor_speed = base_speed + control_signal;

    // モータ速度を0から100の範囲に制限
    left_motor_speed = std::min(left_motor_speed, 100.0);
    right_motor_speed = std::min(right_motor_speed, 100.0);

    std::cout << "Left Motor Speed: " << left_motor_speed << ", Right Motor Speed: " << right_motor_speed << std::endl;

    // 実際のモータ制御関数をここで呼び出す
    ev3_motor_set_power(left_motor, left_motor_speed);
    ev3_motor_set_power(right_motor, right_motor_speed);
        return;
}
