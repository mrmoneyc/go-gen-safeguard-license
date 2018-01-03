rem generate licenses for the sample code with 30 day timeouts from today and also use
rem the customers ethernet address.

@echo off
setlocal enableextensions
for /f "tokens=*" %%a in (
'..\..\bin\pshostid -ethernet -x'
) do (
set id=%%a
)
for /f "tokens=*" %%a in (
'..\..\bin\pshostid -username -x'
) do (
set user=%%a
)
for /f "tokens=*" %%a in (
'..\..\bin\pshostid -hostname -x'
) do (
set host=%%a
)
for /f "tokens=*" %%a in (
'.\sgarc4 encrypt qwerty %user%-%host%'
) do (
set vendor=%%a
)
for /f "tokens=*" %%a in (
'..\..\bin\sggendate 30'
) do (
set dt=%%a
)

rem node-locked license
..\..\bin\pskeycode rc4 monitor 5.0 30-day-trial any %dt% > monitor.lic

rem floating license
..\..\bin\pskeycode rc4 monitor 5.0 %id% ethernet %dt% 10 localhost 29750 > float.lic
..\..\bin\pskeycode rc4 process 5.0 %id% ethernet %dt% 10 >> float.lic
..\..\bin\pskeycode rc4 widget 6.0 %id% ethernet %dt% 10 >> float.lic

..\..\bin\pskeycode rc4 monitor 5.0 %vendor% vendor %dt% > vendor.lic
endlocal
