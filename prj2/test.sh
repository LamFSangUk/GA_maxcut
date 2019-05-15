echo "Copy an instance to maxcut.in file."
echo "cp input/unweighted_to.txt maxcut.in"
cp input/chimera_946.txt maxcut.in

echo ""
echo "make all"
make all

for i in {1..30}
do
    timeout 180 make run 2>&1
    cp maxcut.out "output/result_$i.out"
done

#cp -r output ../../shared/output
mkdir ../../shared/chimera_946
cp -r output ../../shared/chimera_946

echo ""
echo " * 'make clean' before submit or re-run"
echo " * Remove irrelevant print functions before submit."
echo " * Your program must end before time limit."
echo ""        
