message("ADDING [POKERCORE] FROM [MODULES]...")
set(module_pokerCore_src
  pokerCore.cpp util.cpp
)
add_library(module_pokerCore_src ${module_pokerCore_src})
message("ADDING [POKERCORE] FROM [MODULES] FINISHED!")