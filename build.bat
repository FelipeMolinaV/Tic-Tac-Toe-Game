@echo off
IF NOT EXIST builddir (
    echo "Creando carpeta de build y configurando meson..."
    meson setup builddir
    echo "Copiando SDL3.dll..."
    copy /Y "C:\libs\SDL3-3.4.0\x86_64-w64-mingw32\bin\SDL3.dll" "builddir\"
    copy /Y "C:\libs\SDL3_image-3.2.4\x86_64-w64-mingw32\bin\SDL3_image.dll" "builddir\"
    copy /Y "C:\libs\SDL3_ttf-3.2.2\x86_64-w64-mingw32\bin\SDL3_ttf.dll" "builddir\"
    copy /Y "C:\libs\SDL3_mixer_compiled\bin\SDL3_mixer.dll" "builddir\"
)

echo "compilando..."
meson compile -C builddir

echo "Build terminado."

echo "ejecutando build..."

start "" ".\builddir\TicTacToe.exe"
