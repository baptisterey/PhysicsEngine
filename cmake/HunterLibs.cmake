
#GSL from Microsoft project wide integrtation
hunter_add_package(Microsoft.GSL)
#Find librairies loaded by hunter
find_package(Microsoft.GSL CONFIG REQUIRED)
#Link the library for all the projects
link_libraries(Microsoft.GSL::GSL)



#GSL from Microsoft project wide integrtation
hunter_add_package(GTest)
