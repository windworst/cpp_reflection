#include <stdio.h>
#include "reflect.h"

//FileSystem Reflect

REFLECT_CONTEXT(filesystem_ctx)

REFLECT_CLASS(filesystem)
{
public:
	virtual const char* getFilesystemName()
	{
		return "RAW";
	}
};

class fat:public filesystem
{
public:
	virtual const char* getFilesystemName()
	{
		return "FAT";
	}
};

class fat16:public fat
{
public:
	virtual const char* getFilesystemName()
	{
		return "FAT16";
	}
};

class fat32:public fat
{
public:
	virtual const char* getFilesystemName()
	{
		return "FAT32";
	}
};

class exfat:public fat
{
public:
	virtual const char* getFilesystemName()
	{
		return "EXFAT";
	}
};

REFLECT_REGIST(filesystem_ctx,filesystem)
REFLECT_REGIST(filesystem_ctx,fat16)
REFLECT_REGIST(filesystem_ctx,fat32)
REFLECT_REGIST(filesystem_ctx,exfat)

//Operating System Reflect

REFLECT_CONTEXT(os_ctx)

REFLECT_CLASS(os)
{
public:
	virtual const char* getOsName()
	{
		return "Base Os";
	}
};

class windows:public os
{
public:
	virtual const char* getOsName()
	{
		return "windows";
	}
};

class linux:public os
{
public:
	virtual const char* getOsName()
	{
		return "linux";
	}
};

class unix:public os
{
public:
	virtual const char* getOsName()
	{
		return "unix";
	}
};

class android:public os
{
public:
	virtual const char* getOsName()
	{
		return "android";
	}
};

REFLECT_REGIST(os_ctx,os)
REFLECT_REGIST(os_ctx,windows)
REFLECT_REGIST(os_ctx,linux)
REFLECT_REGIST(os_ctx,unix)

int main(int argc, char **argv)
{
	printf("\nfilesystem reflect\n");
	{
		const char* filesystem_list[]=
		{
			"filesystem",
			"fat16","fat32","exfat","ntfs"
		};
		int i;
		for(i=0;i<sizeof(filesystem_list)/sizeof(*filesystem_list);++i)
		{
			filesystem* fs_object = (filesystem*)(new_reflect_object(filesystem_ctx,filesystem_list[i]));
			printf("fs: %s\n",fs_object!=NULL?fs_object->getFilesystemName():"error" );
			delete fs_object;
		}
	}
	printf("\noperating system reflect\n");
	{
		const char* os_list[]=
		{
			"os","windows","linux","unix","android",
		};
		int i;
		for(i=0;i<sizeof(os_list)/sizeof(*os_list);++i)
		{
			os* os_object = (os*)(new_reflect_object(os_ctx,os_list[i]));
			printf("os: %s\n",os_object!=NULL?os_object->getOsName():"error" );
			delete os_object;
		}
	}
	return 0;
}
