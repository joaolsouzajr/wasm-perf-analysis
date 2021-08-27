$build_dir = "./build"
$build_win32_dir = "./build/win32"
if (-Not (Test-Path $build_dir))
{
    New-Item -ItemType Directory -Force -Path $build_dir
}
if (-Not (Test-Path $build_win32_dir))
{
    New-Item -ItemType Directory -Force -Path $build_win32_dir
    Push-Location $build_win32_dir
    cmake.exe -G "Visual Studio 15 2017" -A Win32 ../../
    Pop-Location
}
Push-Location $build_win32_dir
cmake.exe --build . --config Debug
Pop-Location
