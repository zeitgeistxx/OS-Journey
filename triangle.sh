clear
area()
{
	s=`echo "scale=2; ($1 + $2 + $3) / 2"|bc`
	z=`echo "scale=2; $s * ($s - $1) * ($s - $2) * ($s - $3)"|bc`
	echo `echo "scale=2; sqrt($z)"|bc` 
}
echo -n "Enter edge weights of traingle -> "
read a b c
x=`echo "scale=2; $a + $b"|bc`
y=`echo "scale=2; $b + $c"|bc`
z=`echo "scale=2; $a + $c"|bc`
if [ $x -ge $c -a $y -ge $a -a $z -ge $b ]
then
	echo "Triangle is Formable."
	echo "Area of the triangle = `area $a $b $c`sq. unit"
else
	echo "Triangle is not Formable."
fi
