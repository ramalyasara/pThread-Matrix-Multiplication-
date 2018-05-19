
pthread="gcc -o Output/out pthread.c -l pthread"


tread=(1 2 4 8)

	

	if [ -e "Output/pthread.dat" ] 
	then
		rm -rf "Output/pthread.dat"
		touch "Output/pthread.dat"
	else
		touch "Output/pthread.dat"
	fi





echo -e "\n pthread matrix multiplication time for given thread sizes \n"
eval $pthread

for i in "${tread[@]}"
do :
	total="0"
	repeat="4"
	for j in `seq 1 $repeat`
	do :
		result=$(./Output/out $i)
		total=$(bc <<< "scale=8; $total+$result")
	done
	avg=$(bc <<< "scale=10; $total/$repeat")
	echo "$i size of thread using matrix take $avg seconds"
	printf "( $i, $avg )\n" >> "Output/pthread.dat"
done


echo "Process is completed"
echo "Now Generating pdf..."
cd Output
pdflatex Report.tex
echo "Report.pdf is create successfully"
evince Report.pdf
