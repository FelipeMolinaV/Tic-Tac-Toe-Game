@echo off
IF NOT EXIST builddir (
    echo "Creando carpeta de build y configurando meson..."
    meson setup builddir
    echo "Copiando SDL3.dll..."
    copy /Y "C:\libs\SDL3-3.2.26\x86_64-w64-mingw32\bin\SDL3.dll" "builddir\"
)

echo "compilando..."
meson compile -C builddir

echo "Build terminado."

echo "ejecutando build..."

start "" ".\builddir\TicTacToe.exe"
