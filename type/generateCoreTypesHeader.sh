#!/bin/bash

echo '// This header is generated by vuo/type/generateCoreTypesHeader.sh.'

for header in $* ; do
	TYPE=${header%.h}
	echo "#include \"$header\""

	if [[ $header != VuoDictionary_* ]] && [[ $header != "VuoMathExpressionList.h" ]] ; then
		TYPE=VuoList_${header%.h}
		echo "#include \"VuoList_$header\""
	fi
done
