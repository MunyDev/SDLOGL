@echo off
cd C:\Users\avadh\emtest
mkdir .\nginx\html\asset
Xcopy /I /E /y .\asset .\nginx\html\asset > nul

cmd /X /C "C:\Users\avadh\emsdk\emsdk_env.bat > nul & emcc game.cpp -s USE_SDL=2 -s FETCH -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR -o nginx/html/index.html --shell-file shell_minimal.html --preload-file asset"
powershell -command "Compress-Archive -Path .\nginx\html\ -DestinationPath .\archive.zip"



echo [32mBuild finished! Look at http://localhost:8080/ for more instructions...[0m

cd ..
