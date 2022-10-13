#pragma once
#ifndef IMPLEMENT_IF_H_
#define IMPLEMENT_IF_H_

class ImplementIF
{
public:

	virtual bool init() = 0;

	virtual bool activate(bool active) = 0;

	virtual long getFuelLevel() = 0;

	virtual bool isActive() = 0;

	virtual void doCycle() = 0;
};

#endif
