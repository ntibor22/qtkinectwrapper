@echo off
rd /s /q bin
md bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\libgcc_s_dw2-1.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\mingwm10.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtGui4.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtCore4.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtNetwork4.dll bin
copy "C:\Program Files (x86)\OpenNI\Bin\openni.dll" bin

copy example\KinectReader-build-desktop-Qt_4_8_0_for_Desktop_-_MinGW__Qt_SDK__Release\release\KinectReader.exe bin
copy example\KinectLogger-build-desktop-Qt_4_8_0_for_Desktop_-_MinGW__Qt_SDK__Release\release\KinectLogger.exe bin

copy ..\qtffmpegwrapper_trunk\ffmpeg_lib_win32\*.dll bin

cd bin
del ..\..\qtkinectwrapper_win.zip
zip ..\..\qtkinectwrapper_win.zip *
cd ..



