# QtKinectWrapper #
QtKinectWrapper provides a set of Qt classes wrapping the OpenNI/Kinect API. It allows to get depth map, camera image, user skeleton, timestamp, etc.

The wrapper use a background thread to handle the Kinect stuff, which makes it multicore friendly. The threading is entirely transparent to the programmer.


## News ##

  * 07.05.2013:
    * Updated for Qt 5.x (Qt 4.x: need to adjust the .pro file to get the right Qt modules, and change some Qt include path)
    * QtKinectWrapper: Updated to use OpenNI and NiTE 1.5. Version 1.5 removes the need for calibration pose.
      * For windows, use: NITE-Win32-1.5.2.21-Dev.msi, OpenNI-Win32-1.5.4.0-Dev.msi, SensorKinect093-Bin-Win32-v5.1.2.1.msi (PrimeSense Sensor KinectMod 5.1.2.1)

  * 17.03.2012:
    * KinectLogger: Added support for variable frame rate videos (-vfr option) and setting a limit to the video encoding buffer (-vmaxbuf option)

  * 15.03.2012:
    * Added threaded video encoding with backlog - addresses problem when the computer can't keep up with video encoding, at the expense of using more RAM. Check the "backlog" indication in the app status bar to see how many frames haven't yet been encoded. When the user closes the app, it will encoded the backlog of frames. Thus the app may take some time before closing to complete the encoding.
    * Added new APIs to the QtKinectWrapper: getCameraDepthBodies, getCameraDepth.

  * 24.02.2012:
    * Updated install instructions

  * 21.09.2011:
    * KinectLogger can now create a video containing depth map and camera image.


## Wrapper classes ##

### QKinectWrapper: OpenNI/Kinect wrapper class ###
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

## Example programs ##

### Kinect Logger ###

Kinect data acquisition application. It acquires the Kinect data, and stores it to a file, or streams it over TCP for (multiple) client(s). It supports the labeling of relevant event by keypresses. It can create a video of the depth map and camera image.

Acquires and stores/streams:
  * Label
  * Local time, Kinect time, frame number
  * User ID, user status
  * User center of mass (real-world and projected coordinates)
  * Joint coordinates for the 15 skeleton joints (real-world and projected coordinates)


### KinectReader ###

Minimalistic Qt application displaying the camera and depth images, and skeleton.

## Install help ##
(Explanations for windows - likely similar for OSX/Linux)

  * Do not plug the Kinect (alternatively: refuse to let Windows search for drivers on the net)
  * Install openNI, PrimeSense for Kinect, NITE (e.g. from available [here](http://code.google.com/p/qtkinectwrapper/downloads/detail?name=driver_win_openni_1.3.2.1_and_sensor_nite.zip)). Install in this order: OpenNI, then SensorKinect, then NITE.
  * When plugging the Kinect, make sure Windows takes the drivers that were installed in the previous step.
  * Run KinectLogger and KinectReader as admin (known issue).


## Known issues ##
  * KinectLogger and KinectReader must be run with admin rights - this will be addressed in the future