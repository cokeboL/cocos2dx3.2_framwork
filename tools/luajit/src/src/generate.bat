rem SET src="./luaSrc"
rem SET dst="./luaDst"

rem jit = luajit.exe

rem xcopy /E %src% %dst%

rem cd %dst%
for /R %%I in (*.lua) do (
    luajit.exe -b %%I %%I
)

pause

