# within function echo returns the value
clear
factorial() {
	if [ $1 -lt 2 ]; then
		echo 1
	else
		echo $(($1 * $(factorial $(($1 - 1)))))
	fi
}
echo -n "Enter no. of terms and value of x -> "
read n x
pos=0
ans=0
for ((i = 0; i < $n; i++)); do
	y=$(echo "scale=2; $x^$pos/ $(factorial $pos)" | bc)
	ans=$(echo "scale=2; $ans+$y" | bc)
	pos=$((pos + 2))
done
echo $ans
