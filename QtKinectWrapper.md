# Introduction #

QtKinectWrapper provides a set of Qt classes wrapping the OpenNI/Kinect API. It allows to get depth map, camera image, user skeleton, timestamp, etc.

The wrapper use a background thread to handle the Kinect stuff, which makes it multicore friendly. The threading is entirely transparent to the programmer.


# Details #

## QKinectWrapper: OpenNI/Kinect wrapper class ##
Provides functions allowing to conveniently get camera image, depth map, user skeleton, etc:
  * QImage getDepth();
  * QImage getCamera();
  * Bodies getBodies();
  * double getTimestamp();

The signal/slot mechanisms are used to notify the application relevant events::
  * New data (depth map, image, skeleton)
  * Change in Kinect status (initializing, running, idle)
  * User detection
  * Pose detection
  * Calibration detection