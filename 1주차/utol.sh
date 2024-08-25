echo "Working directory"
read dirname

if [ -n "$dirname" ]
then
	cd $dirname
	if [ $? -ne 0 ]
	then
	echo "입력하신 디렉토리를 찾거나 접근할 수 없습니다."
	exit 0
	fi
fi

for dir in *
do

	newname=$(echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]")
	mv $dir $newname
done
