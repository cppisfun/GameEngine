
echo Erstelle und kopiere Dateien der Fremdkomponenten ...

cd boost
bjam -q --toolset=msvc --build-type=minimal --with-filesystem stage
xcopy stage\lib\*.lib ..\..\%1 /i /y /q

echo Dateien der Fremdkomponenten wurden erstellt und kopiert.