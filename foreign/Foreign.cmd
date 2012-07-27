
echo Erstelle und kopiere Dateien der Fremdkomponenten ...

echo Beginne mit boost ...
cd boost
bjam -q --toolset=msvc --build-type=minimal --with-filesystem stage
xcopy stage\lib\*.lib ..\..\%1 /i /y /q
echo boost beendet.

echo Beginne mit irrklang ...
cd ../irrklang
xcopy lib\irrklang.lib ..\..\%1 /i /y /q
echo irrklang beendet.

echo Dateien der Fremdkomponenten wurden erstellt und kopiert.
