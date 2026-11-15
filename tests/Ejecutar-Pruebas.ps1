param(
    [ValidateSet('Debug', 'Release')]
    [string]$Configuracion = 'Debug',
    [ValidateSet('x64', 'Win32')]
    [string]$Plataforma = 'x64'
)

$ErrorActionPreference = 'Stop'
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
if (-not (Test-Path -LiteralPath $vswhere)) {
    throw 'No se encontro Visual Studio Installer. Instala Visual Studio con las herramientas de C++.'
}
$installation = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $installation) { throw 'No se encontraron las herramientas de C++ de Visual Studio.' }
$msbuild = Join-Path $installation 'MSBuild/Current/Bin/MSBuild.exe'
$project = Join-Path $PSScriptRoot 'GatitosLatte.Pruebas.vcxproj'
& $msbuild $project "/p:Configuration=$Configuracion" "/p:Platform=$Plataforma" /verbosity:minimal /nologo
if ($LASTEXITCODE -ne 0) { throw "La compilacion de pruebas fallo ($LASTEXITCODE)." }
$executable = Join-Path $PSScriptRoot "../build/tests/$Plataforma/$Configuracion/GatitosLatte.Pruebas.exe"
& $executable
if ($LASTEXITCODE -ne 0) { throw "Las pruebas fallaron ($LASTEXITCODE)." }
