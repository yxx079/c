#!/bin/bash
# 告诉系统其后路径所指定的程序即是解释此脚本文件的 Shell 程序。

diff="diff -iadwy" #定义变量名

./test_bst.o -v > log_1

sed -n '/label1/,/label2/{/label1/b;/label2/b;p}' log_1 > u_tree.log
sed -n '/label3/,/label4/{/label3/b;/label4/b;p}' log_1 > b_tree.log
#sed 用来处理文件

$diff u_tree.log b_tree.log #使用一个定义过的变量，用$

e_code=$? #	显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误。
if [ $e_code != 0 ]; then
    printf "Part 1 failed : %d\n" "$e_code"
else
    printf "Part 1 OK!\n"
fi

sed -n '$p' log_1
