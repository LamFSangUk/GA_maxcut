for filename in `ls input/`
do
    cp input/$filename maxcut.in

    make all

    for i in {1..30}
    do
        timeout 180 make run 2>&1
        cp maxcut.out "output/result_$i.out"
    done

    name="$(cut -d'.' -f1 <<<$filename)"
    mkdir ../../shared/test/$name
    cp -r output ../../shared/test/$name
done

echo "Phase 1 Done"

echo "Copy"
