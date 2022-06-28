message("ADDING [WRITEFILE] FROM [MODULES]...")
set(module_writeFile_src
  writeFile.cpp
)
add_library(module_writeFile_src ${module_writeFile_src})
message("ADDING [WRITEFILE] FROM [MODULES] FINISHED!")