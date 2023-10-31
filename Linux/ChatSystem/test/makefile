.MK:ALL 
ALL:test json_test
test:mysql.c 
	gcc $^ -o $@ -L /usr/lib64/mysql -lmysqlclient

json_test:json_test.cpp
	g++ $^ -o $@ -ljsoncpp
