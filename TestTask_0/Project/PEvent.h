#pragma once
#include <list>
#include "IEventHandler.h"
template<class ...TParams>
class PEvent
{
	using PEventHandler = IEventHandler<TParams...>;
private:
	std::list<PEventHandler*> m_handlers;
public:
	PEvent() { }
	~PEvent()
	{
		for (PEventHandler* handle : m_handlers)
			delete handle;
		m_handlers.clear();
	};
	void operator()(TParams... params)
	{
		for (PEventHandler* handle : m_handlers)
			handle->call(params...);
	}
	void operator+=(PEventHandler& eventHandler) { m_handlers.push_back(&eventHandler); }
};