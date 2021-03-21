#ifndef YASLOG_HPP
#define YASLOG_HPP

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

template<typename T>
class YasLog
{
	public:
		static void log(std::string prefix, T loggedVariable, std::string postfix)
		{
			std::cout << prefix << loggedVariable << postfix << std::endl;
		}

	private:
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
