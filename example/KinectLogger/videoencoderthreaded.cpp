#include "videoencoderthreaded.h"
#include <QMutexLocker>

VideoEncoderThreaded::VideoEncoderThreaded()
{
   encodedframes=0;
   encodedsize=0;

   delay=1000;
}

VideoEncoderThreaded::~VideoEncoderThreaded()
{
   close();
}


void VideoEncoderThreaded::run()
{
   VideoEncoderThreadedData data;
   unsigned size;
   while(1)
   {
      // Get a reference to the picture to encode
      mutex.lock();
      size = workload.size();
      if(size)
      {
         data = workload.front();
         workload.erase(workload.begin());
      }
      mutex.unlock();

      if(size==0)
      {
         // Nothing to do: sleep a bit
         usleep(10000);
      }
      else
      {
         //printf("VideoEncoderThreaded::run. Workload: %d. Proc %.5f. %d %d %d\n",size,data.t,data.img.width(),data.img.height(),data.img.format());
         // Encode the video
         int s = encoder.encodeImage(data.img);
         encodedsize += s;
         encodedframes++;

         //printf("Encoded size: %d\n",s);
         // Simulate lengthy encodings
         // usleep(delay);
      }

      // Exit only if we have no workload
      if(t_requeststop && workload.size()==0)
         break;
   }
}

/**
   \brief Start to encode videos in the given filename
   Returns true in case of success.
**/
bool VideoEncoderThreaded::createFile(QString filename,unsigned width,unsigned height,unsigned bitrate,unsigned gop,unsigned fps)
{
   // if we're already running, then first terminate the existing task
   if(isRunning())
      close();

   t_requeststop=false;

   bool ok = encoder.createFile(filename,width,height,bitrate,gop,fps);
   if(!ok)
      return ok;

   // Successful -> start the thread for the encoding
   start();
   return true;
}

bool VideoEncoderThreaded::close()
{
   // If we aren't running then we return false
   if(!isRunning())
      return false;

   // Signal the thread that we want it to complete the encoding task
   t_requeststop=true;

   // Wait for the thread to complete it's encoding
   wait();

   // Reset the counters
   encodedframes=0;
   encodedsize=0;

   return encoder.close();

}

int VideoEncoderThreaded::encodeImage(const QImage &img,double t)
{
   QMutexLocker locker(&mutex);
   VideoEncoderThreadedData v;
   v.img = img;
   v.t = t;
   workload.push_back(v);
}

unsigned VideoEncoderThreaded::getEncodedFramesCount()
{
   QMutexLocker locker(&mutex);
   return encodedframes;
}

unsigned VideoEncoderThreaded::getEncodedSize()
{
   QMutexLocker locker(&mutex);
   return encodedsize;
}

unsigned VideoEncoderThreaded::getUnencodedFramesCount()
{
   QMutexLocker locker(&mutex);
   return workload.size();

}

/*void VideoEncoderThreaded::setdel(int value)
{
   QMutexLocker locker(&mutex);
   delay = value*1000;
}*/
