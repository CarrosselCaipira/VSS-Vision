//
// Created by paulo on 19/10/18.
//

#ifndef VSS_VISION_ROBOTTEAMKALMANFILTER_H
#define VSS_VISION_ROBOTTEAMKALMANFILTER_H

#include "IRobotTeamKalmanFilter.h"

class RobotTeamKalmanFilter : public IRobotTeamKalmanFilter {

public:
    RobotTeamKalmanFilter();

    void setRobot(vss::Robot) override;
    void setDeltaTime (double) override;
    void setFoundFlag(bool) override;
    vss::Robot getRobot() override;
    void init() override;

    void predict() override;
    void update() override;

private:
    cv::KalmanFilter kalmanFilter;
    vss::Robot robotMesured;
    vss::Robot robotPredicted;
    double deltaTime;
    bool foundFlag;
    bool foundDelayFlag;
    int notFoundCount;
    int maxNotFoundCount;

    cv::Mat state;
    cv::Mat measure;
};


#endif //VSS_VISION_ROBOTTEAMKALMANFILTER_H
