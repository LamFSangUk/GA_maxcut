echo "Make all"
make all

for file in "input"/planar_amplified_3000.txt
do
    echo "Create 'output' directory"
    mkdir output

    echo ""
    echo $file
    echo "Copy an instance to maxcut.in file."
    cp $file maxcut.in

    filename="$(echo $file | cut -d'/' -f2)"
    filename="$(echo $filename | cut -d'.' -f1)"

    for i in {1..10}
    do
        timeout 500 make run 2>&1
        cp maxcut.out output/result_$i.txt
    done

    echo ""
    echo "Copy all outputs to shared direcotry"
    echo "dir name: "

    mkdir ../../shared/$filename
    cp -r output ../../shared/$filename
    rm -r output
done
