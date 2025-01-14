g++ -Wall -Wextra -pedantic -fsanitize=address -fsanitize=undefined *.c
samplesfolder=$(ls -d */)
testfiles=$(($(ls $samplesfolder | wc -l) / 2 - 1))

echo "Base test:"
for i in $(seq 0 $testfiles)
do
inputfile=$(printf ./%s/%04d_in.txt $samplesfolder $i)
outputfile=$(printf ./%s/%04d_out.txt $samplesfolder $i)
myoutputfile=$(printf ./%s/%04d_myout.txt $samplesfolder $i)
./a.out < $inputfile > $myoutputfile
diff $myoutputfile $outputfile && echo "Test $i OK"
rm $myoutputfile
done
echo ""

echo "Valgrind test:"
g++ -Wall -Wextra -pedantic -g *.c
for i in $(seq 0 $testfiles)
do
inputfile=$(printf ./%s/%04d_in.txt $samplesfolder $i)
valgrind -s --track-origins=yes --leak-check=full ./a.out 2>&1 < $inputfile \
| grep 'ERROR SUMMARY' | awk -v i=$i '{if ($4 == 0){print "Test "i" OK"}else{print "Test", i, ":", $4, "errors"}}'
done
