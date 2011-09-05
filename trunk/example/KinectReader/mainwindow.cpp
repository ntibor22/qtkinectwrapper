#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cio.h"
#include <stdio.h>

#include "QKinectWrapper.h"



MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ConsoleInit();

   // Setup the kinect reader
   kreader.setSkeletonPen(QPen(QBrush(Qt::green),10));
   kreader.setTextPen(QPen(QBrush(Qt::red),50));
   connect(&kreader,SIGNAL(dataNotification()),this,SLOT(kinectData()));
   connect(&kreader,SIGNAL(statusNotification(QKinect::KinectStatus)),this,SLOT(kinectStatus(QKinect::KinectStatus)));
   connect(&kreader,SIGNAL(userNotification(unsigned,bool)),this,SLOT(kinectUser(unsigned,bool)));
   connect(&kreader,SIGNAL(poseNotification(unsigned,QString)),this,SLOT(kinectPose(unsigned,QString)));
   connect(&kreader,SIGNAL(calibrationNotification(unsigned,QKinect::CalibrationStatus)),this,SLOT(kinectCalibration(unsigned,QKinect::CalibrationStatus)));


   sbKinectStatus = new QLabel(statusBar());
   sbKinectFrame = new QLabel(statusBar());
   sbKinectTime = new QLabel(statusBar());
   sbKinectFPS = new QLabel(statusBar());
   sbKinectNumBody = new QLabel(statusBar());
   ui->statusBar->addWidget(sbKinectStatus);
   ui->statusBar->addWidget(sbKinectFrame);
   ui->statusBar->addWidget(sbKinectTime);
   ui->statusBar->addWidget(sbKinectFPS);
   ui->statusBar->addWidget(sbKinectNumBody);
}

MainWindow::~MainWindow()
{
   delete ui;
}



void MainWindow::kinectData()
{
   // Do something
   //printf("kinectData\n");
   sbKinectFrame->setText(QString("Frame %1").arg(kreader.getFrameID()));
   sbKinectTime->setText(QString("Timestamp %1").arg(kreader.getTimestamp()));


   QImage img = kreader.getDepth();
   ui->label->setPixmap(QPixmap::fromImage(img));
   img = kreader.getCamera();
   ui->labelImage->setPixmap(QPixmap::fromImage(img));
   QKinect::Bodies bodies = kreader.getBodies();
   sbKinectNumBody->setText(QString("Body: %1").arg(bodies.size()));
   xnFPSMarkFrame(&xnFPS);
   sbKinectFPS->setText(QString("FPS: %1").arg(xnFPSCalc(&xnFPS)));

   printf("Available bodies: ");
   for(unsigned i=0;i<bodies.size();i++)
      if(bodies[i].tracked)
         printf("%d ",i);
   printf("\n");




}
void MainWindow::kinectStatus(QKinect::KinectStatus s)
{

   QString str("Kinect: ");
   if(s==QKinect::Idle)
      str += "Idle";
   if(s==QKinect::Initializing)
      str += "Initializing";
   if(s==QKinect::OkRun)
      str += "Running";
   if(s==QKinect::ErrorStop)
      str += "Error";
   sbKinectStatus->setText(str);

   if(s==QKinect::ErrorStop || s==QKinect::OkRun || s==QKinect::Idle)
      ui->pushButton_KinectStartStop->setEnabled(true);
   if(s==QKinect::OkRun)
      ui->pushButton_KinectStartStop->setText("Stop Kinect");
   if(s==QKinect::ErrorStop || s==QKinect::Idle)
      ui->pushButton_KinectStartStop->setText("Start Kinect");
}

void MainWindow::kinectPose(unsigned id,QString pose)
{
   printf("User %u: Pose '%s' detected\n",id,pose.toStdString().c_str());
}

void MainWindow::kinectUser(unsigned id, bool found)
{
   printf("User %u: %s\n",id,found?"found":"lost");
}

void MainWindow::kinectCalibration(unsigned id, QKinect::CalibrationStatus s)
{
   printf("User %u: Calibration ",id);
   if(s==QKinect::CalibrationStart)
      printf("started\n");
   if(s==QKinect::CalibrationEndSuccess)
      printf("successful\n");
   if(s==QKinect::CalibrationEndFail)
      printf("failed\n");
}


/*
  Button to start/stop kinect pressed
*/
void MainWindow::on_pushButton_KinectStartStop_clicked()
{
   ui->pushButton_KinectStartStop->setEnabled(false);

   if(kreader.isRunning())
   {
      kreader.stop();
   }
   else
   {
      kreader.start();
      xnFPSInit(&xnFPS, 180);
   }

}
