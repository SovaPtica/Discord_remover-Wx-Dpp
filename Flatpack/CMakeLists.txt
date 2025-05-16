
cmake_minimum_required(VERSION 3.25) # минимальная версия CMAKE

project(mainn) # имя проэкта

# ------Номер
# версии------------------------------------------------------------------
set(${PROJECT_NAME}_VERSION_MAJOR 1.0) # версия проэкта
# set(${PROJECT_NAME}_VERSION_MINOR 2.0) #версия проэкта
# set(${PROJECT_NAME}_VERSION_PATCH 1.0) #версия проэкта
# set(${PROJECT_NAME}_VERSION_TWEAK 1.0) #версия проэкта
# set(${PROJECT_NAME}_VERSION
# "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR") #версия
# проэкта
# указываем какие библиотеки искать Set это папка где искать
#find_package(Poco REQUIRED Foundation)
find_package(dpp REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
#set(wxWidgets_ROOT_DIR "/home/user/Документы/Code/C++/DPP_test/wxDPP/testt_flat/build-dir/files")
#set(wxWidgets_LIB_DIR "/home/user/Документы/Code/C++/DPP_test/wxDPP/testt_flat/build-dir/files/lib")
# ----------------Генерация релиза или дебаг сборки
# ----------------------------------

# set(CMAKE_BUILD_TYPE Debug) set(CMAKE_BUILD_TYPE Relise) #файл релиза
# генерируется по стандарту

# --------------------------- Версия стандарта сборки языка
# -----------------------------

# set(CMAE_CXX_STANDART 11) #Установить версию стандарта set(CMAE_CXX_STANDART
# 14) #Установить версию стандарта set(CMAE_CXX_STANDART 17) #Установить версию
# стандарта or set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")  #флаги
# компилятору set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")  #флаги
# компилятору set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  #флаги
# компилятору set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")  #флаги
# компилятору set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")  #флаги
# компилятору
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23") # флаги компилятору
                                                     # последняя версия
                                                     # стандарта

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89") #для языка c set(CMAKE_C_FLAGS
# "${CMAKE_C_FLAGS} -std=c90") #для языка c set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}
# -std=c99") #для языка c
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17") # для языка c

# ------------------------------------- Добавление каталогов в которых назодится
# проэкт и оптимизация-------

# add_definitions(-Wall -O2) or флаг уровня оптимизации
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2") # флаги  оптимизации
#включает отладочную информацию 
set(CMAKE_BUILD_TYPE Debug)

# --------------Создание исполняемого файла ----------------

# set(SOURCES main.cpp) or
#file(GLOB CPPS "*.cpp" "*/*.cpp") # Добавляются все файлы в дериктории которой
                                  # лежит этот файл

add_executable(${PROJECT_NAME} 
   Drawnig_interface.cpp
   Drowning_wx_menu.cpp
   Discord_remover.cpp
   MyApp.cpp
   MyFrame.cpp
   Save_load_settings.cpp
   )
# --------------------------Создание библиотек-----------------------

# add_library(${PROJECT_NAME}_lib SHARED press_key.cpp class.cpp    )

# add_library(${PROJECT_NAME}_lib::lib_1 ALIAS ${PROJECT_NAME}_lib)

# target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR} )

# ---------------- ГЕнерация библиотек-------------------------------------
# configure_file( "${PROJECT_SOURCE_DIR}"   #для генерации заголовочных файлов
# которые содержат версию и пути :w

# )
include(${wxWidgets_USE_FILE})
# include_directories("${PROJECT_SOURCE_DIR}/нашадиректория") #для подключения
# всех директорий в которых лежат заголовки

# --------------------------Поиск по директориям файлов
# -------------------------------
# add_exacutable(${PROJECT_NAME} main.cpp) #Как в 31 строке только нужно вручную
# указывать все файлы add_exacutable(${PROJECT_NAME} ${SOURCES}) or
#add_executable(${PROJECT_NAME} ${CPPS})

#target_include_directories(${PROJECT_NAME}
#                          PUBLIC /home/repa/boost.1.81.0/include)
# -------------------
target_link_libraries(${PROJECT_NAME}  dpp::dpp)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
#target_link_directories(${PROJECT_NAME} PRIVATE ${POCO_LIB_PATH})
#target_link_libraries(${PROJECT_NAME} PocoFoundation)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib::lib_1 )

# cmake_minimum_required(VERSION 3.5)

# project(Drowning_8 VERSION 1.0)

# find_package(wxWidgets REQUIRED COMPONENTS net core base)
# include(${wxWidgets_USE_FILE})

# include_directories( ${FirstDialog1})
# target_include_directories(${PROJECT_NAME} PRIVATE ${Tutorial_4/FirstDialog1})

# add_executable(${PROJECT_NAME} Drowning_8App.h Drowning_8App.cpp
# Drowning_8Main.h Drowning_8Main.cpp PictureFrame.h Panel1Dialog.h
# Panel1Dialog.cpp NewFrame11.h NewFrame11.cpp )

# target_link_libraries(Drowning_8   ${wxWidgets_LIBRARIES})

# -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# Установка метаданных
install(FILES data/com.remove_discord.MyApp.desktop DESTINATION share/applications)
#install(FILES data/com.example.myapp.metainfo.xml DESTINATION share/metainfo)
# Установка исполняемого файла
install(TARGETS mainn DESTINATION bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
