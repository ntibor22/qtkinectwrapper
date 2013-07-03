@echo off
rd /s /q bin
md bin

copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\libgcc_s_sjlj-1.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\libwinpthread-1.dll bin
copy "C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\libstdc++-6.dll" bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\icuin49.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\icuuc49.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\icudt49.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\Qt5Gui.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\Qt5Widgets.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\Qt5Core.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\Qt5Network.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\libGLESv2.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\D3DCompiler_43.dll bin
copy C:\Qt\Qt5.0.2\5.0.2\mingw47_32\bin\libEGL.dll bin

copy "C:\Program Files (x86)\OpenNI\Bin\openni.dll" bin
copy "C:\Program Files\OpenNI\Bin\openni.dll" bin

copy example\build-KinectReader-desktop\release\KinectReader.exe bin
copy example\build-KinectLogger-desktop\release\KinectLogger.exe bin
copy README bin

copy ..\qtffmpegwrapper_trunk\ffmpeg_lib_win32\*.dll bin


cd bin
del ..\qtkinectwrapper_win.zip
zip ..\qtkinectwrapper_win.zip *
cd ..



