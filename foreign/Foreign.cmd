
echo Erstelle und kopiere Dateien der Fremdkomponenten ...

echo Beginne mit boost ...
cd boost
bjam -q --toolset=msvc --build-type=minimal --with-filesystem stage
xcopy stage\lib\*.lib ..\..\%1 /i /y /q
echo boost beendet.

echo OIS 1.4 unstable ...
cd ..\ois
xcopy lib\*.* ..\..\%1 /i /y/q
echo OIS beendet.

echo Beginne mit Irrlicht 1.7.3 ...
cd ..\irrlicht
xcopy lib\irrlicht.lib ..\..\%1 /i /y /q
xcopy bin\Win32-VisualStudio\irrlicht.dll ..\..\%1 /i /y /q
echo Irrlicht beendet.

echo Beginne mit irrKlang 1.40 ...
cd ..\irrklang
xcopy lib\irrklang.lib ..\..\%1 /i /y /q
xcopy bin\cpp\irrklang.dll ..\..\%1 /i /y /q
echo irrklang beendet.

echo Dateien der Fremdkomponenten wurden erstellt und kopiert.
