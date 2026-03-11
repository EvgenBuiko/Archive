#pragma once
template<class ...TParams>
class IEventHandler
{
public:
	virtual void call(TParams... params) = 0;
protected:
	IEventHandler() {}
};