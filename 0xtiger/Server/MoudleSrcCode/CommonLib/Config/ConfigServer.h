/*
	公共文件里面，难免有一些因为服务端或者客户端的关系，需要做一些小的调整。
	而该文件(ConfigServer.h  ConfigClient.h)就是表明自己身份的一个文件。
	如果你是客户端的程序，那么请在stdafx.h中包含ConfigClient.h
	如果你是服务端的程序，那么请在stdafx.h中包含ConfigServer.h
*/
#pragma once

#define MY_IS_SERVER