mkdir -p ga

echo Enter the number of people: ;read man
echo Enter the number of park: ;read park
echo Enter the number of facility: ;read facility

python gaInput.py $man $park $facility
g++ main.cpp readFile.cpp
./a.out $man $park $facility
