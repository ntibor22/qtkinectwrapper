#ifndef VIDEOENCODERTHREADED_H
#define VIDEOENCODERTHREADED_H

#ifdef WRITEVIDEO

#include <QThread>
#include <QMutex>

#include "QVideoEncoder.h"

#include <list>



typedef struct
{
   QImage img;
   double t;
} VideoEncoderThreadedData;

class VideoEncoderThreaded : public QThread
{
   Q_OBJECT
public:
   VideoEncoderThreaded();
   ~VideoEncoderThreaded();

   bool createFile(QString filename,unsigned width,unsigned height,unsigned bitrate,unsigned gop,unsigned fps=25);
   virtual bool close();

   virtual int encodeImage(const QImage &,double t);
   virtual unsigned getEncodedFramesCount();
   virtual unsigned getEncodedSize();
   virtual unsigned getUnencodedFramesCount();

   void run();

   void setdel(int value);



protected:
   QMutex mutex;
   QVideoEncoder encoder;
   bool t_requeststop;
   unsigned encodedsize;
   unsigned encodedframes;
   std::list<VideoEncoderThreadedData> workload;
   int delay;

};


#endif

#endif // VIDEOENCODERTHREADED_H
