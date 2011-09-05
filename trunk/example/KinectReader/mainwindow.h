#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "QKinectWrapper.h"


#include <XnFPSCalculator.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

public slots:
   void kinectData();
   void kinectStatus(QKinect::KinectStatus);
   void kinectUser(unsigned,bool);
   void kinectPose(unsigned,QString);
   void kinectCalibration(unsigned,QKinect::CalibrationStatus);


private slots:
   void on_pushButton_KinectStartStop_clicked();

private:
   Ui::MainWindow *ui;
   QKinect::QKinectWrapper kreader;
   QLabel *sbKinectStatus;
   QLabel *sbKinectFrame;
   QLabel *sbKinectTime;
   QLabel *sbKinectFPS;
   QLabel *sbKinectNumBody;
   XnFPSData xnFPS;

protected:
};

#endif // MAINWINDOW_H
