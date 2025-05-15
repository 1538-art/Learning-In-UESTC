clear
echo "Input file name:"
read file_name

if [ -f "$file_name" ]
    then
        echo "Starting status observer..."
    else
        echo "File \"$file_name\" does not exist"
        exit 1
fi

current_size=`ls -l $file_name | awk '{print $5}'`
echo "Current file size: $current_size"
checkTime=0
changeTime=0
unchangeTime=0

while true
do
    new_size=`ls -l $file_name | awk '{print $5}'`
    checkTime=`expr $checkTime + 1`
    if [ $new_size -ne $current_size ]
        then
            echo "File size changed from $current_size to $new_size at $checkTime th check"
            changeTime=`expr $changeTime + 1`
            unchangeTime=0
            current_size=$new_size
        else
            echo "File size has not changed at $checkTime th check"
            unchangeTime=`expr $unchangeTime + 1`
    fi

    if [ $unchangeTime -eq 5 ] || [ $changeTime -eq 2 ]
        then
            echo "Observer exited after $checkTime checks with file changed $changeTime times"
            break
    fi

    sleep 2
done