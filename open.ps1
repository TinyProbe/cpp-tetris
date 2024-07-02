$inc_files = ls ./inc/*.hpp
$src_files = ls ./src/*.cpp
$files = ""

for ($i = 0; $i -lt $inc_files.length; ++$i) {
  $files = $files + $inc_files[$i] + " "
  $files = $files + $src_files[$i] + " "
}

$files = $files -replace "C:\\Users\\137ad\\Projects\\desktop\\tetris\\", ""
$files = $files -split " "

nvim inc/tetris.h src/tetris.cc $files[0..($files.length - 2)]
