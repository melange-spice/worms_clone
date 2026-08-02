main.exe: build/input_handler.o build/game.o build/debris.o build/dummy.o build/map.o build/missile.o build/phy_engine.o build/phy_obj.o build/tank.o build/main.o build/linked_list.o
	@printf "Linking: %-22s ===================> %s\n" "*.o files" "main.exe"
	@g++ -fdiagnostics-color=always -g build/main.o  build/game.o build/input_handler.o build/debris.o  build/dummy.o  build/map.o  build/missile.o  build/phy_engine.o  build/phy_obj.o  build/tank.o -o main.exe -L"libraries" -lraylib -lgdi32 -lwinmm


build/tank.o: src/tank.cpp headers/tank.h
	@printf "Compiling: %-20s ===================> %s\n" "tank.cpp" "tank.o"
	@g++ -fdiagnostics-color=always -g -c "src/tank.cpp" -o "build/tank.o" -iquote "headers"


build/phy_obj.o: src/phy_obj.cpp headers/phy_obj.h
	@printf "Compiling: %-20s ===================> %s\n" "phy_obj.cpp" "phy_obj.o"
	@g++ -fdiagnostics-color=always -g -c "src/phy_obj.cpp" -o "build/phy_obj.o" -iquote "headers"


build/phy_engine.o: src/phy_engine.cpp headers/phy_engine.h
	@printf "Compiling: %-20s ===================> %s\n" "phy_engine.cpp" "phy_engine.o"
	@g++ -fdiagnostics-color=always -g -c "src/phy_engine.cpp" -o "build/phy_engine.o" -iquote "headers"


build/missile.o: src/missile.cpp headers/missile.h
	@printf "Compiling: %-20s ===================> %s\n" "missile.cpp" "missile.o"
	@g++ -fdiagnostics-color=always -g -c "src/missile.cpp" -o "build/missile.o" -iquote "headers"


build/map.o: src/map.cpp headers/map.h
	@printf "Compiling: %-20s ===================> %s\n" "map.cpp" "map.o"
	@g++ -fdiagnostics-color=always -g -c "src/map.cpp" -o "build/map.o" -iquote "headers"


build/dummy.o: src/dummy.cpp headers/dummy.h
	@printf "Compiling: %-20s ===================> %s\n" "dummy.cpp" "dummy.o"
	@g++ -fdiagnostics-color=always -g -c "src/dummy.cpp" -o "build/dummy.o" -iquote "headers"


build/debris.o: src/debris.cpp headers/debris.h
	@printf "Compiling: %-20s ===================> %s\n" "debris.cpp" "debris.o"
	@g++ -fdiagnostics-color=always -g -c "src/debris.cpp" -o "build/debris.o" -iquote "headers"


build/main.o: src/main.cpp
	@printf "Compiling: %-20s ===================> %s\n" "main.cpp" "main.o"
	@g++ -fdiagnostics-color=always -g -c "src/main.cpp" -o "build/main.o" -iquote "headers"

build/linked_list.o: headers/linked_list.h
	@printf "Compiling: %-20s ===================> %s\n" "linked_list.h" "linked_list.o"
	@g++ -fdiagnostics-color=always -g -c "headers/linked_list.h" -o "build/linked_list.o" -iquote "headers"

build/game.o: src/game.cpp headers/game.h
	@printf "Compiling: %-20s ===================> %s\n" "game.cpp" "game.o"
	@g++ -fdiagnostics-color=always -g -c "src/game.cpp" -o "build/game.o" -iquote "headers"

build/input_handler.o: src/input_handler.cpp headers/input_handler.h
	@printf "Compiling: %-20s ===================> %s\n" "input_handler.cpp" "input_handler.o"
	@g++ -fdiagnostics-color=always -g -c "src/input_handler.cpp" -o "build/input_handler.o" -iquote "headers"	