message("ADDING [MAIN] FROM [MODULES]...")
set(module_main_src
  main.cpp
)
add_library(module_main_src ${module_main_src})
message("ADDING [MAIN] FROM [MODULES] FINISHED!")