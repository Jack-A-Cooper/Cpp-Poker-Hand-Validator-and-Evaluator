message("ADDING [READFILE] FROM [MODULES]...")
set(module_readFile_src
  readFile.cpp
)
add_library(module_readFile_src ${module_readFile_src})
message("ADDING [READFILE] FROM [MODULES] FINISHED!")