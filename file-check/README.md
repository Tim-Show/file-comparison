使用	gcc md5.c main_md5.c record.c scan.c  -o record

./record  pathname pathname

ex :./record /usr/include /usr/sbin

执行命令后生成对应的记录文件 usr-binmd5.txt usr-includemd5.txt

进入 hash目录 gcc hash.c inspection.c -o inspection

./inspection *.txt *.txt

txt是需要检查的之前记录的目录下的MD5和现在要检查的相同的目录下的文件的MD5值文件

