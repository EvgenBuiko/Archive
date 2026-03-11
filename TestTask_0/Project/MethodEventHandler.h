#pragma once
#include "IEventHandler.h"
template<class TObject, class ...TParams>
class MethodEventHandler : public IEventHandler<TParams...>  
{
	using TMethod = void(TObject::*)(TParams...);
private:
	TObject& m_obj;
	TMethod m_method;

public:
	MethodEventHandler(TObject& obj, TMethod method) : 
		IEventHandler<TParams...>(),
		m_obj(obj),
		m_method(method)
	{ assert(m_method != nullptr); }
	void call(TParams... params) override final { (m_obj.*m_method)(params...); }
};
template<class TObject, class ...TParams>
IEventHandler<TParams...>& createMethodEventHandler(TObject& object, void(TObject::*method)(TParams...))
{ return *new MethodEventHandler<TObject, TParams...>(object, method); }

#define METHOD_HANDLER(Object, Method) createMethodEventHandler(Object, &Method)
#define MY_METHOD_HANDLER(Method) METHOD_HANDLER(*this, Method)