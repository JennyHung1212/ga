mkdir -p ga

echo Enter the number of people: ;read man
echo Enter the number of park: ;read park
echo Enter the number of facility: ;read facility
echo Enter the budget: ;read budget

<<<<<<< HEAD
python gaInput.py $man $park $facility 
=======
python gaInput.py $man $park $facility
>>>>>>> f50ca2fddebe5d67c18d322334dc67b573526f61
g++ main.cpp 
./a.out $man $park $facility $budget
