#ifndef YASENGINE_HPP
#define YASENGINE_HPP

class YasEngine
{
	bool engineInstantiated = false;
	YasEngine GetInstance();
	void initialization();
};

#endif
