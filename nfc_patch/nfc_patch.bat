:<<"::windows_only"
@echo off
:: Copyright 2024 NXP
:: All rights reserved.
::
:: SPDX-License-Identifier: BSD-3-Clause
::
:<<"::windows_only"< code>

:: Validate number of parameters
IF "%~1"=="" (
    echo Source directory not specified.
    echo Usage: nfc_patch.bat [source] [destination]
    exit /b 1
)
IF "%~2"=="" (
    echo Destination directory not specified.
    echo Usage: nfc_patch.bat [source] [destination]
    exit /b 1
)

SET source=%~1
SET destination=%~2

:: Check if source exists
IF NOT EXIST "%source%" (
    echo Source directory "%source%" does not exist.
    exit /b 1
)

:: Check if destination exists, if not, create it
IF NOT EXIST "%destination%" (
    echo Destinaton directory "%source%" does not exist.
    exit /b 1
)

:: Copy NFC folders from NFC Reader library (PN7462AUPspPackageFull-v05_22_01) to an-kw4x-bluetooth-le-nfc-integration
echo Copying files from "%source%\phOsal" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\phOsal"...
xcopy /E /I "%source%\phOsal\*" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\phOsal\"
echo Copying files from "%source%\NxpNfcRdLib" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\NxpNfcRdLib"...
xcopy /E /I "%source%\NxpNfcRdLib\*" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\NxpNfcRdLib\"
echo Copying files from "%source%\DAL\src\KinetisSDK" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\DAL\src\KinetisSDK"...
xcopy /E /I "%source%\DAL\src\KinetisSDK\*" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\DAL\src\KinetisSDK\"
echo Copying files from "%source%\DAL\inc" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\DAL\inc"...
xcopy /E /I "%source%\DAL\inc\*" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\nfc\DAL\inc\"
echo Copying files from "%source%\NfcrdlibEx1_BasicDiscoveryLoop\src\phApp_Init.c" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"...
xcopy /S /Q /Y /F  "%source%\NfcrdlibEx1_BasicDiscoveryLoop\src\phApp_Init.c" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"
echo Copying files from "%source%\NfcrdlibEx1_BasicDiscoveryLoop\NfcrdlibEx1_BasicDiscoveryLoop.c" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"...
xcopy /S /Q /Y /F "%source%\NfcrdlibEx1_BasicDiscoveryLoop\NfcrdlibEx1_BasicDiscoveryLoop.c" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"
echo Copying files from "%source%\NfcrdlibEx1_BasicDiscoveryLoop\intfs\NfcrdlibEx1_BasicDiscoveryLoop.h" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"...
xcopy /S /Q /Y /F  "%source%\NfcrdlibEx1_BasicDiscoveryLoop\intfs\NfcrdlibEx1_BasicDiscoveryLoop.h" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"
echo Copying files from "%source%\NfcrdlibEx1_BasicDiscoveryLoop\intfs\ph_NxpBuild_App.h" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"...
xcopy /S /Q /Y /F "%source%\NfcrdlibEx1_BasicDiscoveryLoop\intfs\ph_NxpBuild_App.h" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"
echo Copying files from "%source%\NfcrdlibEx1_BasicDiscoveryLoop\intfs\phApp_Init.h" to "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"...
xcopy /S /Q /Y /F "%source%\NfcrdlibEx1_BasicDiscoveryLoop\intfs\phApp_Init.h" "%destination%\kw45b41zevk_w_uart_ncf3320_basic_discovery\source\nfc\*"


::echo Add NFC files to local repository

::git add --all

echo copy nfc-dal-src-kinetissdk.patch to %destination%...
copy nfc-dal-src-kinetissdk.patch %destination%

echo copy source-nfc-basic-discovery-loop.patch to %destination%...
copy source-nfc-basic-discovery-loop.patch %destination%

echo cd %destination%...
cd %destination%

echo git apply nfc-dal-src-kinetissdk.patch --ignore-whitespace...
git apply nfc-dal-src-kinetissdk.patch --ignore-whitespace

echo del nfc-dal-src-kinetissdk.patch
del nfc-dal-src-kinetissdk.patch

echo git apply source-nfc-basic-discovery-loop.patch --ignore-whitespace...
git apply source-nfc-basic-discovery-loop.patch --ignore-whitespace

echo del source-nfc-basic-discovery-loop.patch
del source-nfc-basic-discovery-loop.patch

IF %ERRORLEVEL% EQU 0 (
    echo NFC_Patch applied successfully!
) ELSE (
    echo Error occurred while applying the .
)

exit /b 0