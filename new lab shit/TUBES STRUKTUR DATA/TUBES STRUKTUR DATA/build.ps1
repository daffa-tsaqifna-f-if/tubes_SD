$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root

$exe = Join-Path $root 'mini_ecommerce_elektronik.exe'

Write-Host 'Building (g++ -std=c++17)...'

g++ -std=c++17 -I"$root\include" `
  "$root\src\main.cpp" `
  "$root\src\CategoryTree.cpp" `
  "$root\src\SupplierGraph.cpp" `
  "$root\src\StoreSystem.cpp" `
  "$root\src\Input.cpp" `
  -o "$exe"

Write-Host "Built: $exe"
Write-Host 'Run:'
Write-Host "  & '$exe'"
