clear
g++ $(find . -name "*.cpp") -o :3 $(pkg-config --cflags --libs sdl3 sdl3-image) -fdiagnostics-color=always 2>&1 | perl -pe 's/(?:\e\[[0-9;]*m)*\Kerror(?=:)/ewrrrr/g'
./:3