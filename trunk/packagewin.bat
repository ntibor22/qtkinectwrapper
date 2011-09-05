@echo off
rd /s /q bin
md bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\libgcc_s_dw2-1.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\mingwm10.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtGui4.dll bin
copy C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtCore4.dll bin
copy "C:\Program Files (x86)\OpenNI\Bin\openni.dll" bin
copy example\KinectReader-build-desktop\release\KinectReader.exe bin

cd bin
zip ..\..\qtkinectwrapper_win.zip *
cd ..



