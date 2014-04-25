#pragma once

#include <string.h>

//Reflect base class
class reflect_object
{
	;
};

//Reflect object creater
typedef reflect_object* (*object_newer) ();

//register of class
class class_register
{
public:
	class_register(class_register** p_context,
					const char* name,
					object_newer newer)
	:name(name),newer(newer)
	{
		//Add to reflection static linklist
		if(p_context!=NULL)
		{
			this->next = *p_context;
			*p_context = this;
		}
	}
	reflect_object* new_object(const char* name)
	{
		//Call my self
		if( strcmp(this->name,name)==0)
		{
			return this->newer();
		}

		//Call others (tail call)
		if(this->next==NULL)
		{
			return NULL;
		}
		return this->next->new_object(name);
	}
private:
	const char* name;
	object_newer newer;
	class_register* next;
};

//declare reflect class
#define REFLECT_CLASS(class_name) class class_name:public reflect_object

//context of reflect
#define REFLECT_CONTEXT(context_name) class_register* context_name = NULL;

//regist reflect
#define REFLECT_REGIST(context_name,class_name)	\
static reflect_object* class_name##_newer()		\
{												\
	return new class_name();					\
}												\
static class_register cr_##class_name(&(context_name),#class_name,class_name##_newer);


//reflect create
#define new_reflect_object(reflect_ctx,class_name) ((reflect_ctx)!=NULL?(reflect_ctx)->new_object(class_name):NULL)

