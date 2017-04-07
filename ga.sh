mkdir -p ga

echo Enter the number of people: ;read man
echo Enter the number of park: ;read park
echo Enter the number of facility: ;read facility
echo Enter the budget: ;read budget

python gaInput.py $man $park $facility 
g++ main.cpp 
./a.out $man $park $facility $budget
