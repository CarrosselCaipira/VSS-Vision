#ifndef VSS_VISION_ROBOTRECOGNIZER_H
#define VSS_VISION_ROBOTRECOGNIZER_H

#include "Interfaces/IRobotRecognizer.h"
#include "Domain/Ball.h"
#include "Domain/Robot.h"
#include "Domain/ColorSide.h"
#include "Domain/ColorPosition.h"
#include "Domain/ColorPattern.h"
#include "BallKalmanFilter.h"
#include "RobotTeamKalmanFilter.h"

class RobotRecognizer : public IRobotRecognizer {

public:

    RobotRecognizer();

    void recognizeTeam(ColorPosition, std::vector<ColorPosition>, std::vector<ColorPattern>) override;
    void recognizeOpponent(ColorPosition) override;
    void recognizeBall(ColorPosition) override;

    void setImage(cv::Mat image) override;

    vss::Ball getBall() override;
    std::vector<vss::Robot> getBlueRobots() override;
    std::vector<vss::Robot> getYellowRobots() override;

private:

    cv::Mat image;

    std::vector<vss::Robot> blueRobots;
    std::vector<vss::Robot> yellowRobots;

    std::vector<vss::Robot> lastBlueRobots;
    std::vector<vss::Robot> lastYellowRobots;

    vss::Ball ball;

    double rate;

    ColorSide recognizeSide(double farthestAngle, double closestAngle);
    vss::Robot calculateRobotSpeedsAndFilter(unsigned int id, vss::Robot robot);


    vss::Robot convertRobotPosePixelToCentimeter(vss::Robot);
    void convertBallPosePixelToCentimeter();

    BallKalmanFilter ballKalmanFilter;
    std::vector<RobotTeamKalmanFilter> robotsTeamKalmanFilter;

    void keepOpponentOrder(ColorType);

    bool init;

};

#endif
