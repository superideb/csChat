#定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

#表示生成可执行文件ChatServer,由SRC_LIST变量所定义的源文件编译而来
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

#表示server这个目标程序,需要连接muduo_net muduo_base pthread这三个库文件(库之间可能有先后依赖关系，注意顺序)
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)

