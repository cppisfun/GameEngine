
echo Erstelle und kopiere Dateien der Fremdkomponenten ...

echo Beginne mit boost 1.53.0 ...
cd boost
bjam -q --toolset=msvc --build-type=minimal --with-filesystem stage
xcopy stage\lib\*.lib ..\..\%1 /i /y /q
echo boost beendet.

echo Beginne mit TinyXML++ 2.5.3 ...
cd ..\TinyXML++
xcopy %1\ticpp.lib ..\..\%1 /i /y /q
echo TinyXML++ beendet.

echo Beginne mit SDL 2.0.3 ...
cd ..\SDL
xcopy SDL2\lib\x86\*.lib ..\..\%1 /i /y /q
xcopy SDL2\lib\x86\*.dll ..\..\%1 /i /y /q
xcopy SDL2_image\lib\x86\*.lib ..\..\%1 /i /y /q
xcopy SDL2_image\lib\x86\*.dll ..\..\%1 /i /y /q
xcopy SDL2_ttf\lib\x86\*.lib ..\..\%1 /i /y /q
xcopy SDL2_ttf\lib\x86\*.dll ..\..\%1 /i /y /q
echo SDL beendet.

echo Beginne mit irrKlang 1.4.0 ...
cd ..\irrklang
xcopy lib\irrklang.lib ..\..\%1 /i /y /q
xcopy bin\cpp\irrklang.dll ..\..\%1 /i /y /q
echo irrklang beendet.

echo Dateien der Fremdkomponenten wurden erstellt und kopiert.
