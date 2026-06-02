@echo off
setlocal

set "SOURCE=main.cpp"
set "OUTPUT=sandbox.exe"

if not "%~1"=="" set "SOURCE=%~1"
if not "%~2"=="" set "OUTPUT=%~2"

where g++ >nul 2>nul
if errorlevel 1 (
  echo g++ not found. Install MinGW-w64 and ensure g++ is on PATH.
  exit /b 1
)

g++ -Wall -Wextra -std=c++17 "%SOURCE%" -o "%OUTPUT%"
if errorlevel 1 exit /b 1

".\%OUTPUT%"
