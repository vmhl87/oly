for file in *; do trim=`echo $file | sed s/$1\ // | sed s/silver\ problem\ // | sed s/,//`; mv "$file" "$trim"; done
