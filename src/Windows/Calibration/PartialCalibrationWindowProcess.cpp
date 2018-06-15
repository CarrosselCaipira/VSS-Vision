/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Repositories/CalibrationRepository.h>
#include <CameraReader.h>
#include <Windows/Calibration/CalibrationWindow.h>

void CalibrationWindow::receiveNewFrame(cv::Mat _frame){
  frame = _frame;
  dispatcher_update_gtkmm_frame.emit();

  countFps();
}

void CalibrationWindow::updateGtkImage(){
  //TimeHelper t;
  //t.startCounting();
  processFrame();
  //std::cout << t.getElapsedTime() << std::endl;
  screenImage->set_image(frame);
}

void CalibrationWindow::processFrame() {
  changeRotation(frame, calibration.rotation);

  if(calibration.shouldCropImage) {
      cropImage(frame, calibration.cut[0], calibration.cut[1]);
  }

  colorRecognizer->processImage(frame);

  applyRectangleToFrame();
}

void CalibrationWindow::applyRectangleToFrame(){
  auto rectangles = colorRecognizer->getRectangles();
  for(unsigned int i = 0 ; i < rectangles.size() ; i++){
    cv::rectangle(frame, rectangles.at(i), cv::Scalar(255, 255, 255), 1, 1, 0);
  }
}

void CalibrationWindow::countFps(){
  if(timeHelper.getElapsedTime() >= 1000){
    updateFpsLabel();
    timeHelper.restartCounting();
    fpsAmount = 0;

  } else {
    fpsAmount++;
  }
}
