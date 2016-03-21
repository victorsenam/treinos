ST=A

for x in $(eval echo {$ST..$1})
do
    mkdir $x
    cp $2/code_temp.cpp $x/$x.cpp
done
