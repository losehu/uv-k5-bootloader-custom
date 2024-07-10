@echo off
setlocal

set "target_directory=./"

for /r "%target_directory%" %%f in (*.o *.d) do (
    del "%%f"
)

echo Deletion complete.
endlocal

