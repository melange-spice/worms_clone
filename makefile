main.exe: build/input_handler.o build/game.o build/debris.o build/dummy.o build/map.o build/missile.o build/phy_engine.o build/phy_obj.o build/tank.o build/main.o build/linked_list.o
	@printf "Linking: %-22s ===================> %s\n" "*.o files" "main.exe"
	@g++ -fdiagnostics-color=always -g build/main.o  build/game.o build/input_handler.o build/debris.o  build/dummy.o  build/map.o  build/missile.o  build/phy_engine.o  build/phy_obj.o  build/tank.o -o main.exe -L"libraries" -lraylib -lgdi32 -lwinmm


build/tank.o: src/tank.cpp src/headers/tank.hpp
	@printf "Compiling: %-20s ===================> %s\n" "tank.cpp" "tank.o"
	@g++ -fdiagnostics-color=always -g -c "src/tank.cpp" -o "build/tank.o" -I "include"


build/phy_obj.o: src/phy_obj.cpp src/headers/phy_obj.hpp
	@printf "Compiling: %-20s ===================> %s\n" "phy_obj.cpp" "phy_obj.o"
	@g++ -fdiagnostics-color=always -g -c "src/phy_obj.cpp" -o "build/phy_obj.o" -I "include"


build/phy_engine.o: src/phy_engine.cpp src/headers/phy_engine.hpp
	@printf "Compiling: %-20s ===================> %s\n" "phy_engine.cpp" "phy_engine.o"
	@g++ -fdiagnostics-color=always -g -c "src/phy_engine.cpp" -o "build/phy_engine.o" -I "include"


build/missile.o: src/missile.cpp src/headers/missile.hpp
	@printf "Compiling: %-20s ===================> %s\n" "missile.cpp" "missile.o"
	@g++ -fdiagnostics-color=always -g -c "src/missile.cpp" -o "build/missile.o" -I "include"


build/map.o: src/map.cpp src/headers/map.hpp
	@printf "Compiling: %-20s ===================> %s\n" "map.cpp" "map.o"
	@g++ -fdiagnostics-color=always -g -c "src/map.cpp" -o "build/map.o" -I "include"


build/dummy.o: src/dummy.cpp src/headers/dummy.hpp
	@printf "Compiling: %-20s ===================> %s\n" "dummy.cpp" "dummy.o"
	@g++ -fdiagnostics-color=always -g -c "src/dummy.cpp" -o "build/dummy.o" -I "include"


build/debris.o: src/debris.cpp src/headers/debris.hpp
	@printf "Compiling: %-20s ===================> %s\n" "debris.cpp" "debris.o"
	@g++ -fdiagnostics-color=always -g -c "src/debris.cpp" -o "build/debris.o" -I "include"


build/main.o: src/main.cpp
	@printf "Compiling: %-20s ===================> %s\n" "main.cpp" "main.o"
	@g++ -fdiagnostics-color=always -g -c "src/main.cpp" -o "build/main.o" -I "include"

build/linked_list.o: src/headers/linked_list.hpp
	@printf "Compiling: %-20s ===================> %s\n" "linked_list.hpp" "linked_list.o"
	@g++ -fdiagnostics-color=always -g -c "headers/linked_list.hpp" -o "build/linked_list.o" -I "include"

build/game.o: src/game.cpp src/headers/game.hpp
	@printf "Compiling: %-20s ===================> %s\n" "game.cpp" "game.o"
	@g++ -fdiagnostics-color=always -g -c "src/game.cpp" -o "build/game.o" -I "include"

build/input_handler.o: src/input_handler.cpp src/headers/input_handler.hpp
	@printf "Compiling: %-20s ===================> %s\n" "input_handler.cpp" "input_handler.o"
	@g++ -fdiagnostics-color=always -g -c "src/input_handler.cpp" -o "build/input_handler.o" -I "include"	